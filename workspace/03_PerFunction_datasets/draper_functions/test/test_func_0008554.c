foreign_group(void)
{
  int ngroups, i;
  gid_t *list = get_group_list(&ngroups);

  qsort(list, ngroups, sizeof(*list), compare_groups);

  for (i=1; i<ngroups; ++i)
    {

      const gid_t nextval = 1+list[i-1];

      if (nextval < list[i] )
        {

          return nextval;
        }
    }


  if (ngroups)
    {
      if (list[0] > 0)
        return 0;
      else
        return 1+list[ngroups-1];
    }
  else
    {
      gid_t last_resort = getegid();
      if (last_resort > 0)
        return 0;
      else
        return 1+last_resort;
    }
}
