/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013 Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include "State.h"

#include "Context.h"
#include "Extensions.h"
#include "Implementation/BufferState.h"
#include "Implementation/DebugState.h"
#include "Implementation/FramebufferState.h"
#include "Implementation/MeshState.h"
#include "Implementation/RendererState.h"
#include "Implementation/ShaderState.h"
#include "Implementation/ShaderProgramState.h"
#include "Implementation/TextureState.h"

namespace Magnum { namespace Implementation {

State::State(Context& context):
    buffer(new BufferState),
    debug(new DebugState(context)),
    framebuffer(new FramebufferState),
    mesh(new MeshState),
    renderer(new RendererState),
    shader(new ShaderState),
    shaderProgram(new ShaderProgramState),
    texture(new TextureState)
{

    Debug() << "Using optional features:";

    if(context.isExtensionSupported<Extensions::GL::KHR::debug>())
        Debug() << "   " << Extensions::GL::KHR::debug::string();
    else {
        if(context.isExtensionSupported<Extensions::GL::EXT::debug_label>())
            Debug() << "   " << Extensions::GL::EXT::debug_label::string();

        if(context.isExtensionSupported<Extensions::GL::EXT::debug_marker>())
            Debug() << "   " << Extensions::GL::EXT::debug_marker::string();
        #ifndef MAGNUM_TARGET_GLES
        else if(context.isExtensionSupported<Extensions::GL::GREMEDY::string_marker>())
            Debug() << "   " << Extensions::GL::GREMEDY::string_marker::string();
        #endif
    }
}

State::~State() {
    delete texture;
    delete shaderProgram;
    delete shader;
    delete renderer;
    delete mesh;
    delete framebuffer;
    delete debug;
    delete buffer;
}

}}