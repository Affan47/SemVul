vbo_exec_FlushVertices( struct gl_context *ctx, GLuint flags )
{
   struct vbo_exec_context *exec = &vbo_context(ctx)->exec;

#ifdef DEBUG

   exec->flush_call_depth++;
   assert(exec->flush_call_depth == 1);
#endif

   if (_mesa_inside_begin_end(ctx)) {

#ifdef DEBUG
      exec->flush_call_depth--;
      assert(exec->flush_call_depth == 0);
#endif
      return;
   }


   vbo_exec_FlushVertices_internal(exec, GL_TRUE);


   ctx->Driver.NeedFlush &= ~(FLUSH_UPDATE_CURRENT | flags);

#ifdef DEBUG
   exec->flush_call_depth--;
   assert(exec->flush_call_depth == 0);
#endif
}
