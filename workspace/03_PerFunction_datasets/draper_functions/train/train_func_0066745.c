jbg_enc_lrlmax(struct jbg_enc_state *s, unsigned long x,
		   unsigned long y)
{
  for (s->d = 0; s->d < 6; s->d++)
    if (jbg_ceil_half(s->xd, s->d) <= x && jbg_ceil_half(s->yd, s->d) <= y)
      break;
  s->dl = 0;
  s->dh = s->d;
  jbg_set_default_l0(s);
  return s->d;
}
