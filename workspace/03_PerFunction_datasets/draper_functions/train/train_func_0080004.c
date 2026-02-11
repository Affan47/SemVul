probe_wavpack(bgav_input_context_t * input)
  {
  uint32_t fourcc;
  if(bgav_input_get_fourcc(input, &fourcc) &&
     (fourcc == BGAV_MK_FOURCC('w','v','p','k')))
    return 1;
  return 0;
  }
