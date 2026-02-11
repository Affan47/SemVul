yy_Strike(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;  yyDo(ctx, yyPush, 2, 0);
  yyprintf((stderr, "%s\n", "Strike"));  yyText(ctx, ctx->begin, ctx->end);  if (!( extension(EXT_STRIKE) )) goto l643;  if (!yymatchString(ctx, "~~")) goto l643;
  {  int yypos644= ctx->pos, yythunkpos644= ctx->thunkpos;  if (!yy_Whitespace(ctx)) goto l644;  goto l643;
  l644:;	  ctx->pos= yypos644; ctx->thunkpos= yythunkpos644;
  }  if (!yy_StartList(ctx)) goto l643;  yyDo(ctx, yySet, -2, 0);
  {  int yypos647= ctx->pos, yythunkpos647= ctx->thunkpos;  if (!yymatchString(ctx, "~~")) goto l647;  goto l643;
  l647:;	  ctx->pos= yypos647; ctx->thunkpos= yythunkpos647;
  }  if (!yy_Inline(ctx)) goto l643;  yyDo(ctx, yySet, -1, 0);  yyDo(ctx, yy_1_Strike, ctx->begin, ctx->end);
  l645:;
  {  int yypos646= ctx->pos, yythunkpos646= ctx->thunkpos;
  {  int yypos648= ctx->pos, yythunkpos648= ctx->thunkpos;  if (!yymatchString(ctx, "~~")) goto l648;  goto l646;
  l648:;	  ctx->pos= yypos648; ctx->thunkpos= yythunkpos648;
  }  if (!yy_Inline(ctx)) goto l646;  yyDo(ctx, yySet, -1, 0);  yyDo(ctx, yy_1_Strike, ctx->begin, ctx->end);  goto l645;
  l646:;	  ctx->pos= yypos646; ctx->thunkpos= yythunkpos646;
  }  if (!yymatchString(ctx, "~~")) goto l643;  yyDo(ctx, yy_2_Strike, ctx->begin, ctx->end);
  yyprintf((stderr, "  ok   %s @ %s\n", "Strike", ctx->buf+ctx->pos));  yyDo(ctx, yyPop, 2, 0);
  return 1;
  l643:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "Strike", ctx->buf+ctx->pos));
  return 0;
}
