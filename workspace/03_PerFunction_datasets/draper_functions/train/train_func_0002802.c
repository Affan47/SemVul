output_newlen(struct jbg85_enc_state *s)
{
  unsigned char buf[6];

  assert(s->i == 0);
  if (s->newlen != 1)
    return;
  buf[0] = MARKER_ESC;
  buf[1] = MARKER_NEWLEN;
  buf[2] =  s->y0 >> 24;
  buf[3] = (s->y0 >> 16) & 0xff;
  buf[4] = (s->y0 >>  8) & 0xff;
  buf[5] =  s->y0        & 0xff;
  s->data_out(buf, 6, s->file);
  s->newlen = 2;
  if (s->y == s->y0) {


    buf[1] = MARKER_SDNORM;
    s->data_out(buf, 2, s->file);
  }
}
