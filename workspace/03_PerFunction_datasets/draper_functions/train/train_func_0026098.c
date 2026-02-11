_mesa_PopName( void )
{
   GET_CURRENT_CONTEXT(ctx);

   if (ctx->RenderMode != GL_SELECT) {
      return;
   }

   FLUSH_VERTICES(ctx, _NEW_RENDERMODE);
   if (ctx->Select.HitFlag) {
      write_hit_record( ctx );
   }
   if (ctx->Select.NameStackDepth == 0) {
      _mesa_error( ctx, GL_STACK_UNDERFLOW, "glPopName" );
   }
   else
      ctx->Select.NameStackDepth--;
}
