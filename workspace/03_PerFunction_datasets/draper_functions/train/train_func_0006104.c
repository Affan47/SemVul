yy_NonblankIndentedLine(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "NonblankIndentedLine"));
  {  int yypos1353= ctx->pos, yythunkpos1353= ctx->thunkpos;  if (!yy_BlankLine(ctx)) goto l1353;  goto l1352;
  l1353:;	  ctx->pos= yypos1353; ctx->thunkpos= yythunkpos1353;
  }  if (!yy_IndentedLine(ctx)) goto l1352;
  yyprintf((stderr, "  ok   %s @ %s\n", "NonblankIndentedLine", ctx->buf+ctx->pos));
  return 1;
  l1352:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "NonblankIndentedLine", ctx->buf+ctx->pos));
  return 0;
}
