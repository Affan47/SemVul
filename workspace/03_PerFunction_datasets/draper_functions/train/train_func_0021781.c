uniqstr_new (char const *str)
{
  uniqstr res = hash_lookup (uniqstrs_table, str);
  if (!res)
    {

      res = xstrdup (str);
      if (!hash_insert (uniqstrs_table, res))
        xalloc_die ();
    }
  return res;
}
