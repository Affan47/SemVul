parse_m3u(bgav_redirector_context_t * r)
  {
  char * buffer = NULL;
  int buffer_alloc = 0;
  char * pos;

  while(1)
    {
    if(!bgav_input_read_line(r->input, &buffer, &buffer_alloc, 0, NULL))
      break;
    pos = strip_spaces(buffer);
    if((*pos == '#') || (*pos == '\0'))
      continue;
    if(!strcmp(pos, "--stop--"))
      break;

    else
      {
      add_url(r);
      r->urls[r->num_urls-1].url = bgav_strdup(pos);
      }
    }

  if(buffer)
    free(buffer);
  return !!(r->num_urls);
  }
