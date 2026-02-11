bgav_input_ensure_buffer_size(bgav_input_context_t * ctx, int len)
  {
  int result;
  if(ctx->buffer_size < len)
    {
    if(ctx->buffer_size + len > ctx->buffer_alloc)
      {
      ctx->buffer_alloc += len + 64;
      ctx->buffer = realloc(ctx->buffer, ctx->buffer_alloc);
      }
    result =
      ctx->input->read(ctx, &ctx->buffer[ctx->buffer_size],
                      len - ctx->buffer_size);
    if(result < 0)
      result = 0;
    ctx->buffer_size += result;
#if 0
    if(ctx->do_buffer)
      {
      ctx->buffer_size +=
        ctx->input->read_nonblock(ctx, ctx->buffer + ctx->buffer_size,
                                  ctx->buffer_alloc - ctx->buffer_size);
      }
#endif
    }
  }
