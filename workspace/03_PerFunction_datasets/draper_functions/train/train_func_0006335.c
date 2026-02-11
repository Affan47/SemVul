step1 (pixma_t * s)
{
  int error;
  iclass_t *mf = (iclass_t *) s->subdriver;

  error = query_status (s);
  if (error < 0)
    return error;
  if (s->param->source == PIXMA_SOURCE_ADF && !has_paper (s))
    return PIXMA_ENO_PAPER;

  if (mf->generation == 1)
    {
      if (error >= 0)
        error = activate (s, 0);
      if (error >= 0)
        error = activate (s, 4);
    }
  return error;
}
