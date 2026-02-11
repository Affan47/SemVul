_mesa_set_program_error(struct gl_context *ctx, GLint pos, const char *string)
{
   ctx->Program.ErrorPos = pos;
   free((void *) ctx->Program.ErrorString);
   if (!string)
      string = "";
   ctx->Program.ErrorString = _mesa_strdup(string);
}
