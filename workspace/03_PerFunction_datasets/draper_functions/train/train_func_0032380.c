_mesa_LoadName( GLuint name )
{
   GET_CURRENT_CONTEXT(ctx);

   if (ctx->RenderMode != GL_SELECT) {
      return;
   }
   if (ctx->Select.NameStackDepth == 0) {
      _mesa_error( ctx, GL_INVALID_OPERATION, "glLoadName" );
      return;
   }

   FLUSH_VERTICES(ctx, _NEW_RENDERMODE);

   if (ctx->Select.HitFlag) {
      write_hit_record( ctx );
   }
   if (ctx->Select.NameStackDepth < MAX_NAME_STACK_DEPTH) {
      ctx->Select.NameStack[ctx->Select.NameStackDepth-1] = name;
   }
   else {
      ctx->Select.NameStack[MAX_NAME_STACK_DEPTH-1] = name;
   }
}
