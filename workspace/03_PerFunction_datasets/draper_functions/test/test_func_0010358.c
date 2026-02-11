evgl_glBindFramebuffer(GLenum target, GLuint framebuffer)
{
   Render_Engine_GL_Context *ctx = current_evgl_ctx;

   if (!ctx)
     {
        ERR("No current context set.");
        return;
     }


   if (framebuffer==0)
     {
        if (gl_direct_enabled)
           glBindFramebuffer(target, 0);
        else
           glBindFramebuffer(target, ctx->context_fbo);
        ctx->current_fbo = 0;
     }
   else
     {
        glBindFramebuffer(target, framebuffer);


        ctx->current_fbo = framebuffer;
     }
}
