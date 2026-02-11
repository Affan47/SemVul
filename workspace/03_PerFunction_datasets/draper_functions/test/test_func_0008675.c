r128_parse(struct r128_ctx *ctx, struct r128_image *img, u_int8_t *symbols, int len)
{
  int table = 0, i;
  char outbuf[1024];
  int pos = 0, ppos = 0;


  if(len < 3)
    return R128_EC_SYNTAX;


  if(!(ctx->flags & R128_FL_NOCKSUM))
    if(r128_cksum(symbols, len - 2) != symbols[len - 2])
      return R128_EC_CHECKSUM;

  outbuf[0] = 0;

  for(i = 0; i<len; i++)
  {
    int c = symbols[i], nb = 0;

    if(c == 103)
      table = 0;
    else if(c == 104)
      table = 1;
    else if(c == 105)
      table = 2;
    else if(c == 99 && table != 2)
      table = 2;
    else if(c == 100 && table != 1)
      table = 1;
    else if(c == 101 && table != 0)
      table = 0;
    else if(c == 106)
      return r128_report_code(ctx, img, outbuf, ppos);
    else if(c < 0 && c > 105)
      nb = sprintf(outbuf + pos, " - ?? %d ?? - ", c);
    else
      nb = sprintf(outbuf + pos, "%s", code_tables[table][c]);

    ppos = pos; pos += nb;
  }
  return R128_EC_NOEND;
}
