SHA512_final_transform(SHA512_ctx* ctx)
{
  unsigned mlen = ctx->bytes % 128;
  ctx->M[mlen++] = 0x80;
  memset(ctx->M + mlen, 0x00, 128 - mlen);
  if (mlen > 128-16) {
    SHA512_transform(ctx->H, ctx->M);
    memset(ctx->M, 0x00, 128-16);
  }

  uint64_pack_msb(ctx->bytes >> 61, ctx->M+112);
  uint64_pack_msb(ctx->bytes <<  3, ctx->M+120);
  SHA512_transform(ctx->H, ctx->M);
}
