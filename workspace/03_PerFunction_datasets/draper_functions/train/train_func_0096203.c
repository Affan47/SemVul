kwsmusts (void)
{
  struct dfamust const *dm;
  char const *err;

  dm = dfamusts (dfa);
  if (dm)
    {
      kwsinit (&kwset);


      for (; dm; dm = dm->next)
        {
          if (!dm->exact)
            continue;
          ++kwset_exact_matches;
          if ((err = kwsincr_case (dm->must)) != NULL)
            error (EXIT_TROUBLE, 0, "%s", err);
        }


      for (dm = dfamusts (dfa); dm; dm = dm->next)
        {
          if (dm->exact)
            continue;
          if ((err = kwsincr_case (dm->must)) != NULL)
            error (EXIT_TROUBLE, 0, "%s", err);
        }
      if ((err = kwsprep (kwset)) != NULL)
        error (EXIT_TROUBLE, 0, "%s", err);
    }
}
