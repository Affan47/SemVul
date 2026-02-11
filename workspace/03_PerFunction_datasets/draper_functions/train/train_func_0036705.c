jbg85_enc_newlen(struct jbg85_enc_state *s, unsigned long newlen)
{
  unsigned char buf[6];

  if (s->newlen == 2 || newlen >= s->y0 || newlen < 1 ||
      !(s->options & JBG_VLENGTH)) {

    return;
  }
  if (newlen < s->y) {

    newlen = s->y;
  }
  if (s->y > 0 && s->y0 != newlen)
    s->newlen = 1;
  s->y0 = newlen;
  if (s->y == s->y0) {

    if (s->i > 0) {
      arith_encode_flush(&s->s);
      buf[0] = MARKER_ESC;
      buf[1] = MARKER_SDNORM;
      s->data_out(buf, 2, s->file);
      s->i = 0;
    }

    output_newlen(s);
  }
}
