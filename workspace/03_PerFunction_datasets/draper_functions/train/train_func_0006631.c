MD5Init(struct MD5Context *ctx, int brokenEndian) {
  ctx->buf[0] = 0x67452301;
  ctx->buf[1] = 0xefcdab89;
  ctx->buf[2] = 0x98badcfe;
  ctx->buf[3] = 0x10325476;

  ctx->bits[0] = 0;
  ctx->bits[1] = 0;


  if (brokenEndian) {
    ctx->doByteReverse = 0;
  } else {
    ctx->doByteReverse = 1;
  }


}
