find_dfsnum_interval (struct dom_dfsnum *defs, unsigned n, unsigned s)
{
  unsigned f = 0, t = n, m;

  while (t > f + 1)
    {
      m = (f + t) / 2;
      if (defs[m].dfs_num <= s)
	f = m;
      else
	t = m;
    }

  return defs[f].bb_index;
}
