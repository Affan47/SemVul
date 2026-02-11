yy_StyleBlock(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "StyleBlock"));  yyText(ctx, ctx->begin, ctx->end);  if (!(YY_BEGIN)) goto l1475;  if (!yy_InStyleTags(ctx)) goto l1475;  yyText(ctx, ctx->begin, ctx->end);  if (!(YY_END)) goto l1475;
  l1476:;
  {  int yypos1477= ctx->pos, yythunkpos1477= ctx->thunkpos;  if (!yy_BlankLine(ctx)) goto l1477;  goto l1476;
  l1477:;	  ctx->pos= yypos1477; ctx->thunkpos= yythunkpos1477;
  }  yyDo(ctx, yy_1_StyleBlock, ctx->begin, ctx->end);
  yyprintf((stderr, "  ok   %s @ %s\n", "StyleBlock", ctx->buf+ctx->pos));
  return 1;
  l1475:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "StyleBlock", ctx->buf+ctx->pos));
  return 0;
}
