get_framebuffer_target(struct gl_context *ctx, GLenum target)
{
   bool have_fb_blit = _mesa_is_gles3(ctx) || _mesa_is_desktop_gl(ctx);
   switch (target) {
   case GL_DRAW_FRAMEBUFFER:
      return have_fb_blit ? ctx->DrawBuffer : NULL;
   case GL_READ_FRAMEBUFFER:
      return have_fb_blit ? ctx->ReadBuffer : NULL;
   case GL_FRAMEBUFFER_EXT:
      return ctx->DrawBuffer;
   default:
      return NULL;
   }
}
