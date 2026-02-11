tuple_evalctx_reset(TupleEvalContext *ctx)
{
  int i;

  for (i = 0; i < ctx->nvariables; i++)
    if (ctx->variables[i]) {
      ctx->variables[i]->fieldread = FALSE;
      ctx->variables[i]->fieldvalid = FALSE;
      str_unref (ctx->variables[i]->fieldstr);
      ctx->variables[i]->fieldstr = NULL;
    }
}
