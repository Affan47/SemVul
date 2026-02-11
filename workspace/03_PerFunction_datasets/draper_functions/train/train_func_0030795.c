_mesa_free_program_data(struct gl_context *ctx)
{
   _mesa_reference_vertprog(ctx, &ctx->VertexProgram.Current, NULL);
   _mesa_delete_program_cache(ctx, ctx->VertexProgram.Cache);
   _mesa_reference_fragprog(ctx, &ctx->FragmentProgram.Current, NULL);
   _mesa_delete_shader_cache(ctx, ctx->FragmentProgram.Cache);
   _mesa_reference_geomprog(ctx, &ctx->GeometryProgram.Current, NULL);
   _mesa_delete_program_cache(ctx, ctx->GeometryProgram.Cache);


   if (ctx->ATIFragmentShader.Current) {
      ctx->ATIFragmentShader.Current->RefCount--;
      if (ctx->ATIFragmentShader.Current->RefCount <= 0) {
         free(ctx->ATIFragmentShader.Current);
      }
   }

   free((void *) ctx->Program.ErrorString);
}
