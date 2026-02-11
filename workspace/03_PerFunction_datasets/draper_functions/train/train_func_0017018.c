md5_finish_ctx (struct md5_ctx *ctx, void *resbuf)
{

  uint32_t bytes = ctx->buflen;
  size_t size = (bytes < 56) ? 64 / 4 : 64 * 2 / 4;


  ctx->total[0] += bytes;
  if (ctx->total[0] < bytes)
    ++ctx->total[1];


  ctx->buffer[size - 2] = SWAP (ctx->total[0] << 3);
  ctx->buffer[size - 1] = SWAP ((ctx->total[1] << 3) | (ctx->total[0] >> 29));

  memcpy (&((char *) ctx->buffer)[bytes], fillbuf, (size - 2) * 4 - bytes);


  md5_process_block (ctx->buffer, size * 4, ctx);

  return md5_read_ctx (ctx, resbuf);
}
