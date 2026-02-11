bgav_input_read_convert_line(bgav_input_context_t * input,
                                 char ** buffer, int * buffer_alloc,
                                 int * len)
  {
  int line_alloc = 0;
  char * line = NULL;
  int in_len, out_len;
  int64_t old_pos = input->position;

  if(!input->charset || !strcmp(input->charset, "UTF-8"))
    return bgav_input_read_line(input, buffer, buffer_alloc, 0,
                                len);
  else
    {
    if(!input->cnv)
      input->cnv = bgav_charset_converter_create(input->opt, input->charset, "UTF-8");

    if(!bgav_input_read_line(input, &line, &line_alloc, 0, &in_len))
      return 0;

    bgav_convert_string_realloc(input->cnv,
                                line, in_len,
                                &out_len,
                                buffer, buffer_alloc);
    if(len) *len = out_len;
    if(line) free(line);

    return input->position - old_pos;
    }
  }
