_mesa_tex_target_to_index(const struct gl_context *ctx, GLenum target)
{
   switch (target) {
   case GL_TEXTURE_1D:
      return _mesa_is_desktop_gl(ctx) ? TEXTURE_1D_INDEX : -1;
   case GL_TEXTURE_2D:
      return TEXTURE_2D_INDEX;
   case GL_TEXTURE_3D:
      return ctx->API != API_OPENGLES ? TEXTURE_3D_INDEX : -1;
   case GL_TEXTURE_CUBE_MAP:
      return ctx->Extensions.ARB_texture_cube_map
         ? TEXTURE_CUBE_INDEX : -1;
   case GL_TEXTURE_RECTANGLE:
      return _mesa_is_desktop_gl(ctx) && ctx->Extensions.NV_texture_rectangle
         ? TEXTURE_RECT_INDEX : -1;
   case GL_TEXTURE_1D_ARRAY:
      return _mesa_is_desktop_gl(ctx) && ctx->Extensions.EXT_texture_array
         ? TEXTURE_1D_ARRAY_INDEX : -1;
   case GL_TEXTURE_2D_ARRAY:
      return (_mesa_is_desktop_gl(ctx) && ctx->Extensions.EXT_texture_array)
         || _mesa_is_gles3(ctx)
         ? TEXTURE_2D_ARRAY_INDEX : -1;
   case GL_TEXTURE_BUFFER:
      return ctx->API == API_OPENGL_CORE &&
             ctx->Extensions.ARB_texture_buffer_object ?
             TEXTURE_BUFFER_INDEX : -1;
   case GL_TEXTURE_EXTERNAL_OES:
      return _mesa_is_gles(ctx) && ctx->Extensions.OES_EGL_image_external
         ? TEXTURE_EXTERNAL_INDEX : -1;
   case GL_TEXTURE_CUBE_MAP_ARRAY:
      return _mesa_is_desktop_gl(ctx) && ctx->Extensions.ARB_texture_cube_map_array
         ? TEXTURE_CUBE_ARRAY_INDEX : -1;
   case GL_TEXTURE_2D_MULTISAMPLE:
      return _mesa_is_desktop_gl(ctx) && ctx->Extensions.ARB_texture_multisample
         ? TEXTURE_2D_MULTISAMPLE_INDEX: -1;
   case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:
      return _mesa_is_desktop_gl(ctx) && ctx->Extensions.ARB_texture_multisample
         ? TEXTURE_2D_MULTISAMPLE_ARRAY_INDEX: -1;
   default:
      return -1;
   }
}
