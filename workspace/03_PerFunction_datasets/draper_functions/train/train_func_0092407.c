get_group_array (ngp)
     int *ngp;
{
  int i;
  static int *group_iarray = (int *)NULL;

  if (group_iarray)
    {
      if (ngp)
	*ngp = ngroups;
      return (group_iarray);
    }

  if (ngroups == 0)
    initialize_group_array ();

  if (ngroups <= 0)
    {
      if (ngp)
	*ngp = 0;
      return (int *)NULL;
    }

  group_iarray = (int *)xmalloc (ngroups * sizeof (int));
  for (i = 0; i < ngroups; i++)
    group_iarray[i] = (int)group_array[i];

  if (ngp)
    *ngp = ngroups;
  return group_iarray;
}
