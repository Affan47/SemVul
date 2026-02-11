is_pure_ghost(int hist_ix) const
{
  return hist_ix >= 0 ? _is_pure_ghost[hist_ix] : false;
}
