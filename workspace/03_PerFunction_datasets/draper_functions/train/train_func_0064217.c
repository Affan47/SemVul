yy_AposChunk(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "AposChunk"));  yyText(ctx, ctx->begin, ctx->end);  if (!( extension(EXT_SMART) )) goto l305;  if (!yymatchChar(ctx, '\'')) goto l305;
  {  int yypos306= ctx->pos, yythunkpos306= ctx->thunkpos;  if (!yy_Alphanumeric(ctx)) goto l305;  ctx->pos= yypos306; ctx->thunkpos= yythunkpos306;
  }  yyDo(ctx, yy_1_AposChunk, ctx->begin, ctx->end);
  yyprintf((stderr, "  ok   %s @ %s\n", "AposChunk", ctx->buf+ctx->pos));
  return 1;
  l305:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "AposChunk", ctx->buf+ctx->pos));
  return 0;
}
