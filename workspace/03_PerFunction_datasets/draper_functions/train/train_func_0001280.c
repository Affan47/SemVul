_mesa_CallList(GLuint list)
{
   GLboolean save_compile_flag;
   GET_CURRENT_CONTEXT(ctx);
   FLUSH_CURRENT(ctx, 0);

   if (MESA_VERBOSE & VERBOSE_API)
      _mesa_debug(ctx, "glCallList %d\n", list);

   if (list == 0) {
      _mesa_error(ctx, GL_INVALID_VALUE, "glCallList(list==0)");
      return;
   }

   if (0)
      mesa_print_display_list( list );


   save_compile_flag = ctx->CompileFlag;
   if (save_compile_flag) {
      ctx->CompileFlag = GL_FALSE;
   }

   execute_list(ctx, list);
   ctx->CompileFlag = save_compile_flag;


   if (save_compile_flag) {
      ctx->CurrentDispatch = ctx->Save;
      _glapi_set_dispatch(ctx->CurrentDispatch);
   }
}
