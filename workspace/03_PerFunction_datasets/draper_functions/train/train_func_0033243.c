ReportOverflows(boolean_g hard)
{
  lump_t *cur;

  if (hard)
  {
    PrintMsg(
      "ERRORS.  The following levels failed to be built, and won't\n"
      "work in any Doom port (and may even crash it).\n\n"
    );
  }
  else
  {
    PrintMsg(
      "POTENTIAL FAILURES.  The following levels should work in a\n"
      "modern Doom port, but may fail (or even crash) in older ports.\n\n"
    );
  }

  for (cur=wad.dir_head; cur; cur=cur->next)
  {
    level_t *lev = cur->lev_info;

    int limits, one_lim;

    if (! (lev && ! (lev->flags & LEVEL_IS_GL)))
      continue;

    limits = hard ? lev->hard_limit : lev->soft_limit;

    if (limits == 0)
      continue;

    for (one_lim = (1<<20); one_lim; one_lim >>= 1)
    {
      if (limits & one_lim)
        ReportOneOverflow(cur, one_lim, hard);
    }
  }
}
