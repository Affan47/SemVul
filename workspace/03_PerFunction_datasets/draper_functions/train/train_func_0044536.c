flickcurl_build_tags_from_string(flickcurl* fc, flickcurl_photo* photo,
                                 const char *string, int *tag_count_p)
{
  flickcurl_tag** tags = NULL;
  int nodes_count;
  int tag_count;
  int i;

  nodes_count = 0;
  for(i = 0; string[i]; i++) {
    if(string[i] == ' ')
      nodes_count++;
  }

  tags = (flickcurl_tag**)calloc(sizeof(flickcurl_tag*), nodes_count+1);

  for(i = 0, tag_count = 0; i < nodes_count; i++) {
    flickcurl_tag* t;
    const char *p = string;
    size_t len;

    t = (flickcurl_tag*)calloc(sizeof(flickcurl_tag), 1);
    t->photo = photo;

    while(*p && *p != ' ')
      p++;

    len = p-string;

    t->cooked = (char*)malloc(len + 1);
    memcpy(t->cooked, string, len);
    t->cooked[len] = '\0';

    if(fc->tag_handler)
      fc->tag_handler(fc->tag_data, t);

    tags[tag_count++] = t;


    string = p+1;
  }

  if(tag_count_p)
    *tag_count_p = tag_count;

  return tags;
}
