yy_Quoted(yycontext *ctx)
{  int yypos0= ctx->pos, yythunkpos0= ctx->thunkpos;
  yyprintf((stderr, "%s\n", "Quoted"));
  {  int yypos60= ctx->pos, yythunkpos60= ctx->thunkpos;  if (!yymatchChar(ctx, '"')) goto l61;
  l62:;
  {  int yypos63= ctx->pos, yythunkpos63= ctx->thunkpos;
  {  int yypos64= ctx->pos, yythunkpos64= ctx->thunkpos;  if (!yymatchChar(ctx, '"')) goto l64;  goto l63;
  l64:;	  ctx->pos= yypos64; ctx->thunkpos= yythunkpos64;
  }  if (!yymatchDot(ctx)) goto l63;  goto l62;
  l63:;	  ctx->pos= yypos63; ctx->thunkpos= yythunkpos63;
  }  if (!yymatchChar(ctx, '"')) goto l61;  goto l60;
  l61:;	  ctx->pos= yypos60; ctx->thunkpos= yythunkpos60;  if (!yymatchChar(ctx, '\'')) goto l59;
  l65:;
  {  int yypos66= ctx->pos, yythunkpos66= ctx->thunkpos;
  {  int yypos67= ctx->pos, yythunkpos67= ctx->thunkpos;  if (!yymatchChar(ctx, '\'')) goto l67;  goto l66;
  l67:;	  ctx->pos= yypos67; ctx->thunkpos= yythunkpos67;
  }  if (!yymatchDot(ctx)) goto l66;  goto l65;
  l66:;	  ctx->pos= yypos66; ctx->thunkpos= yythunkpos66;
  }  if (!yymatchChar(ctx, '\'')) goto l59;
  }
  l60:;
  yyprintf((stderr, "  ok   %s @ %s\n", "Quoted", ctx->buf+ctx->pos));
  return 1;
  l59:;	  ctx->pos= yypos0; ctx->thunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "Quoted", ctx->buf+ctx->pos));
  return 0;
}
