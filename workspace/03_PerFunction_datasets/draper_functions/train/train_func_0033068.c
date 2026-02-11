read_dmlh(bgav_input_context_t * input, dmlh_t * ret,
                     chunk_header_t * ch)
  {
  int64_t start_pos;

  start_pos = input->position;
  if(!bgav_input_read_32_le(input, &ret->dwTotalFrames))
    return 0;

  if(input->position - start_pos < ch->ckSize)
    {
    bgav_input_skip(input, PADD(ch->ckSize) - (input->position - start_pos));
    }
  return 1;
  }
