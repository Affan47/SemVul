probe_pls(bgav_input_context_t * input)
  {
  char probe_data[10];

  if(input->mimetype &&
     (!strcmp(input->mimetype, "audio/x-scpls") ||
      !strcmp(input->mimetype, "audio/scpls")))
    return 1;


  if(bgav_input_get_data(input, (uint8_t*)probe_data, 10) < 10)
    return 0;

  if(!strncasecmp(probe_data, "[playlist]", 10))
    return 1;
  return 0;
  }
