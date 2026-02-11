yy_NormalChar(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "NormalChar"));
  {  int yypos453= ctx->pos, yythunkpos453= ctx->thunkpos;
  {  int yypos454= ctx->pos, yythunkpos454= ctx->thunkpos;  if (!yy_SpecialChar(ctx)) goto l455;  goto l454;
  l455:;	  ctx->pos= yypos454; ctx->thunkpos= yythunkpos454;  if (!yy_Spacechar(ctx)) goto l456;  goto l454;
  l456:;	  ctx->pos= yypos454; ctx->thunkpos= yythunkpos454;  if (!yy_Newline(ctx)) goto l453;
  }
  l454:;	  goto l452;
  l453:;	  ctx->pos= yypos453; ctx->thunkpos= yythunkpos453;
  }  if (!yymatchDot(ctx)) goto l452;
  yyprintf((stderr, "  ok   %s @ %s\n", "NormalChar", ctx->buf+ctx->pos));
  return 1;
  l452:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "NormalChar", ctx->buf+ctx->pos));
  return 0;
}
