check_codec(uint32_t wav_id, const uint32_t * list)
  {
  int index = 0;
  while(list[index] != 0x00)
    {
    if(wav_id == list[index])
      return 1;
    index++;
    }
  return 0;
  }
