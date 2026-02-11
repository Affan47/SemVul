sha256_final(struct sha256_ctx *md, uint8_t *out) {
  unsigned i;

  if (md->curlen >= sizeof(md->buf)) return;


  md->length += md->curlen * 8;


  md->buf[md->curlen++] = (uint8_t)0x80;


  if (md->curlen > 56) {
    while (md->curlen < 64) {
      md->buf[md->curlen++] = (uint8_t)0;
    }
    sha256_transform(md->state, md->buf);
    md->curlen = 0;
  }


  while (md->curlen < 56) {
    md->buf[md->curlen++] = (uint8_t)0;
  }


  put64_msb(md->length, md->buf + 56);
  sha256_transform(md->state, md->buf);


  for (i = 0; i < 8; i += 2) {
    put32_msb(md->state[i], out + (4 * i));
    put32_msb(md->state[i + 1], out + (4 * (i + 1)));
  }
}
