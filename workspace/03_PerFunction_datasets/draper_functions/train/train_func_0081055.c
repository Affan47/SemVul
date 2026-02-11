bgav_id3v1_read(bgav_input_context_t * input)
  {

  char buffer[128];
  char * pos;

  bgav_id3v1_tag_t * ret;
  bgav_charset_converter_t * cnv;

  if(bgav_input_read_data(input, (uint8_t*)buffer, 128) < 128)
    return NULL;

  cnv = bgav_charset_converter_create(input->opt, "ISO-8859-1", "UTF-8");

  ret = calloc(1, sizeof(*ret));

  pos = buffer + 3;
  ret->title = get_string(cnv, pos, 30);

  pos = buffer + 33;
  ret->artist = get_string(cnv, pos, 30);

  pos = buffer + 63;
  ret->album = get_string(cnv, pos, 30);

  pos = buffer + 93;
  ret->year = get_string(cnv, pos, 4);

  pos = buffer + 97;
  ret->comment = get_string(cnv, pos, 30);
  if(ret->comment && strlen(ret->comment) <= 28)
    ret->track = buffer[126];
  ret->genre = buffer[127];

  bgav_charset_converter_destroy(cnv);

  return ret;
  }
