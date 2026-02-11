md5_finish_ctx (struct md5_ctx *ctx, void *resbuf)
{

  md5_uint32 bytes = ctx->buflen;
  md5_uint32 swap_bytes;
  size_t pad;


  ctx->total[0] += bytes;
  if (ctx->total[0] < bytes)
    ++ctx->total[1];

  pad = bytes >= 56 ? 64 + 56 - bytes : 56 - bytes;
  memcpy (&ctx->buffer[bytes], fillbuf, pad);


  swap_bytes = SWAP (ctx->total[0] << 3);
  memcpy (&ctx->buffer[bytes + pad], &swap_bytes, sizeof (swap_bytes));
  swap_bytes = SWAP ((ctx->total[1] << 3) | (ctx->total[0] >> 29));
  memcpy (&ctx->buffer[bytes + pad + 4], &swap_bytes, sizeof (swap_bytes));


  md5_process_block (ctx->buffer, bytes + pad + 8, ctx);

  return md5_read_ctx (ctx, resbuf);
}
