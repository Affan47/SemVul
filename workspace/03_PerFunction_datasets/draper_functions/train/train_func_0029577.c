next_startcode(uint8_t * data, int len)
  {
  int ret;
  ret = (data[5]<<24) | (data[6]<<16) | (data[7]<<8) | (data[8]);
  if(!ret)
    ret = 13;
  return ret;
  }
