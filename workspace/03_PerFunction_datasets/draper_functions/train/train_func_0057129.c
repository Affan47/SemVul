cgd_is_spatial (GfsFunction * f)
{
  guint i;
  for (i = 0; i < f->g->N; i++)
    if (f->index[i] < 3)
      return TRUE;
  return FALSE;
}
