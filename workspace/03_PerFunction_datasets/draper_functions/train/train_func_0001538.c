ss_init(ss_context *ctx, FILE *handle)
{
  if (NULL == ctx)
    return TRUE;

  ctx->ret = (char *)malloc(sizeof(char) * FUZZY_MAX_RESULT);
  if (ctx->ret == NULL)
    return TRUE;

  if (handle != NULL)
    ctx->total_chars = find_file_size(handle);

  ctx->block_size = MIN_BLOCKSIZE;
  while (ctx->block_size * SPAMSUM_LENGTH < ctx->total_chars) {
    ctx->block_size = ctx->block_size * 2;
  }

  return FALSE;
}
