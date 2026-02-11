parse_ref(bgav_redirector_context_t * r)
  {
  char * buffer = NULL;
  int buffer_alloc = 0;
  char * pos;

  if(!bgav_input_read_line(r->input, &buffer, &buffer_alloc, 0, NULL))
    return 0;

  if(strncasecmp(buffer, "[Reference]", 11))
    return 0;

  while(1)
    {
    if(!bgav_input_read_line(r->input, &buffer, &buffer_alloc, 0, NULL))
      break;

    if(!strncasecmp(buffer, "ref", 3) && isdigit(buffer[3]))
      {
      pos = strchr(buffer, '=');
      if(pos)
        {
        pos++;
        r->num_urls++;
        r->urls = realloc(r->urls, r->num_urls * sizeof(*(r->urls)));
        memset(r->urls + r->num_urls - 1, 0, sizeof(*(r->urls)));

        r->urls[r->num_urls-1].name = bgav_sprintf("Stream %d (%s)",
                                                   r->num_urls,
                                                   pos);
        if(!strncasecmp(pos, "http://", 7))
          r->urls[r->num_urls-1].url = bgav_sprintf("mmsh%s", pos+4);
        else
          r->urls[r->num_urls-1].url = bgav_sprintf("%s", pos);
        }
      }
    }
  return 1;
  }
