extractSelectedContent()
{
  TextLocation dot[2];
  XPoint xy[2];
  long range[2];

  MSString selection("");
  unsigned int len = 0;

  range[0] = _regions[0].range[0];
  range[1] = _regions[0].range[1];

  locations(range, 2, dot, xy);
  if (range[0] < range[1])
  for (Snip *s = dot[0].snip; s; s = s->next) {
    if (s->content.head && s->length > 0 &&
	s->content.head->bytes * s->length > 0) {
      char *buf = (char*)malloc(s->length + 1);
      strncpy(buf, (char *)(&s->data[s->content.head->bytes * s->offset]),
							s->length);
      buf[s->length - 1] = '\0';
      selection << buf;
      len += s->length;
      selection = selection(0, len);
      if (s->endseq) { selection << "\n"; len ++; }
      free(buf);
    }
    if (s == dot[1].snip) break;
  }
  return selection;
}
