mkv_read_uint_small(bgav_input_context_t * ctx, int * ret, int bytes)
  {
  uint64_t val;
  if(!mkv_read_uint(ctx, &val, bytes))
    return 0;
  *ret = val;
  return 1;
  }
