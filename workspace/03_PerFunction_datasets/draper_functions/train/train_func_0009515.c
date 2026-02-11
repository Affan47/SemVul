yymatchClass(yycontext *ctx, unsigned char *bits)
{
  int c;
  if (ctx->pos >= ctx->limit && !yyrefill(ctx)) return 0;
  c= (unsigned char)ctx->buf[ctx->pos];
  if (bits[c >> 3] & (1 << (c & 7)))
    {
      ++ctx->pos;
      yyprintf((stderr, "  ok   yymatchClass @ %s\n", ctx->buf+ctx->pos));
      return 1;
    }
  yyprintf((stderr, "  fail yymatchClass @ %s\n", ctx->buf+ctx->pos));
  return 0;
}
