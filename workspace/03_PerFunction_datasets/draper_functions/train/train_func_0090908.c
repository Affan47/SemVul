gegl_expcombine_new_exposure (void)
{
  exposure *e = g_new (exposure, 1);
  e->hi = e->lo = e;

  memset (e->pixels, 0, sizeof (e->pixels));
  e->ti = NAN;

  return e;
}
