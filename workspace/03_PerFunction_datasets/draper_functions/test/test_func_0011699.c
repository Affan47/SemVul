find_domain_parms_idx (const char *name)
{
  int idx, aliasno;


  for (idx = 0; domain_parms[idx].desc; idx++)
    if (!strcmp (name, domain_parms[idx].desc))
      return idx;


  if (!domain_parms[idx].desc)
    {
      for (aliasno = 0; curve_aliases[aliasno].name; aliasno++)
        if (!strcmp (name, curve_aliases[aliasno].other))
          break;
      if (curve_aliases[aliasno].name)
        {
          for (idx = 0; domain_parms[idx].desc; idx++)
            if (!strcmp (curve_aliases[aliasno].name, domain_parms[idx].desc))
              return idx;
        }
    }

  return -1;
}
