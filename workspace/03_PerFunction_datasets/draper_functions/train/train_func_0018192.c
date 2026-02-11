parse_text_node(parser_t * p, bgav_yml_node_t * ret)
  {
  char * pos;
  pos = find_chars(p, "<");
  if(!pos)
    return 0;
  ret->str = bgav_strndup(p->buffer, pos);
  advance(p, (int)(pos - p->buffer));
  return 1;
  }
