intelInvalidateState(struct gl_context * ctx, GLuint new_state)
{
   struct brw_context *brw = brw_context(ctx);

   if (ctx->swrast_context)
      _swrast_InvalidateState(ctx, new_state);
   _vbo_InvalidateState(ctx, new_state);

   brw->NewGLState |= new_state;
}
