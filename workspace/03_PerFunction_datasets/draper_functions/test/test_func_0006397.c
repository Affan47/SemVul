bgav_yml_probe(bgav_input_context_t * input)
  {
  char * ptr, *end_ptr;
  char probe_data[PROBE_LEN+1];
  int len;
  len = bgav_input_get_data(input, (uint8_t*)probe_data, PROBE_LEN);

  probe_data[len] = '\0';

  ptr = probe_data;

  while(isspace(*ptr) && (*ptr != '\0'))
    ptr++;


  if(*ptr == '\0')
    return 0;

  end_ptr = strchr(ptr, '\n');
  if(!end_ptr)
    return 0;
  *end_ptr = '\0';

  if(bgav_match_regexp(ptr, YML_REGEXP))
    return 1;
  return 0;
  }
