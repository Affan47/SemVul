bgav_mxf_klv_read(bgav_input_context_t * input, mxf_klv_t * ret)
  {
  uint8_t c;
  int64_t len;

  if(bgav_input_read_data(input, ret->key, 16) < 16)
    return 0;


  if(!bgav_input_read_8(input, &c))
    return 0;

  if(c & 0x80)
    {
    len = c & 0x0F;
    ret->length = 0;
    if(len > 8)
      return 0;
    while(len--)
      {
      if(!bgav_input_read_8(input, &c))
        return 0;
      ret->length = (ret->length<<8) | c;
      }
    }
  else
    ret->length = c;

  ret->endpos = input->position + ret->length;


  return 1;
  }
