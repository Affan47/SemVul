_mesa_GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint *params)
{
   struct gl_renderbuffer *rb;
   GET_CURRENT_CONTEXT(ctx);

   if (target != GL_RENDERBUFFER_EXT) {
      _mesa_error(ctx, GL_INVALID_ENUM,
                  "glGetRenderbufferParameterivEXT(target)");
      return;
   }

   rb = ctx->CurrentRenderbuffer;
   if (!rb) {
      _mesa_error(ctx, GL_INVALID_OPERATION,
                  "glGetRenderbufferParameterivEXT");
      return;
   }


   switch (pname) {
   case GL_RENDERBUFFER_WIDTH_EXT:
      *params = rb->Width;
      return;
   case GL_RENDERBUFFER_HEIGHT_EXT:
      *params = rb->Height;
      return;
   case GL_RENDERBUFFER_INTERNAL_FORMAT_EXT:
      *params = rb->InternalFormat;
      return;
   case GL_RENDERBUFFER_RED_SIZE_EXT:
   case GL_RENDERBUFFER_GREEN_SIZE_EXT:
   case GL_RENDERBUFFER_BLUE_SIZE_EXT:
   case GL_RENDERBUFFER_ALPHA_SIZE_EXT:
   case GL_RENDERBUFFER_DEPTH_SIZE_EXT:
   case GL_RENDERBUFFER_STENCIL_SIZE_EXT:
      *params = get_component_bits(pname, rb->_BaseFormat, rb->Format);
      break;
   case GL_RENDERBUFFER_SAMPLES:
      if ((_mesa_is_desktop_gl(ctx) && ctx->Extensions.ARB_framebuffer_object)
          || _mesa_is_gles3(ctx)) {
         *params = rb->NumSamples;
         break;
      }

   default:
      _mesa_error(ctx, GL_INVALID_ENUM,
                  "glGetRenderbufferParameterivEXT(target)");
      return;
   }
}
