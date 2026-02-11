get_number_of_segments (struct context *c)
{
  struct anthy_conv_stat cs;

  if (anthy_get_stat(c->ac, &cs) < 0)
    return -1;

  return cs.nr_segment;
}
