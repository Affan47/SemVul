probe_gif(bgav_input_context_t * input)
  {
  char probe_data[SIG_LEN];
  if(bgav_input_get_data(input, (uint8_t*)probe_data, SIG_LEN) < SIG_LEN)
    return 0;
  if(!memcmp(probe_data, gif_sig, SIG_LEN))
    return 1;
  return 0;
  }
