arith_encode_flush(struct jbg_arenc_state *s)
{
  unsigned long temp;


  if ((temp = (s->a - 1 + s->c) & 0xffff0000L) < s->c)
    s->c = temp + 0x8000;
  else
    s->c = temp;

  s->c <<= s->ct;
  if (s->c & 0xf8000000L) {

    if (s->buffer >= 0) {
      s->byte_out(s->buffer + 1, s->file);
      if (s->buffer + 1 == MARKER_ESC)
	s->byte_out(MARKER_STUFF, s->file);
    }

    if (s->c & 0x7fff800L)
      for (; s->sc; --s->sc)
	s->byte_out(0x00, s->file);
  } else {
    if (s->buffer >= 0)
      s->byte_out(s->buffer, s->file);

    for (; s->sc; --s->sc) {
      s->byte_out(0xff, s->file);
      s->byte_out(MARKER_STUFF, s->file);
    }
  }

  if (s->c & 0x7fff800L) {
    s->byte_out((s->c >> 19) & 0xff, s->file);
    if (((s->c >> 19) & 0xff) == MARKER_ESC)
      s->byte_out(MARKER_STUFF, s->file);
    if (s->c & 0x7f800L) {
      s->byte_out((s->c >> 11) & 0xff, s->file);
      if (((s->c >> 11) & 0xff) == MARKER_ESC)
	s->byte_out(MARKER_STUFF, s->file);
    }
  }

  return;
}
