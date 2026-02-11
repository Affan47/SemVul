has_paper (pixma_t * s)
{
  mp150_t *mp = (mp150_t *) s->subdriver;

  if (is_scanning_from_adfdup (s))
    return (mp->current_status[1] == 0 || mp->current_status[2] == 0);
  else
    return (mp->current_status[1] == 0);
}
