display_target_tables (void)
{
  int t;
  int columns;
  int ret = 1;
  char *colum;

  columns = 0;
  colum = getenv ("COLUMNS");
  if (colum != NULL)
    columns = atoi (colum);
  if (columns == 0)
    columns = 80;

  t = 0;
  while (bfd_target_vector[t] != NULL)
    {
      int oldt = t, wid;

      wid = LONGEST_ARCH + strlen (bfd_target_vector[t]->name) + 1;
      ++t;
      while (wid < columns && bfd_target_vector[t] != NULL)
	{
	  int newwid;

	  newwid = wid + strlen (bfd_target_vector[t]->name) + 1;
	  if (newwid >= columns)
	    break;
	  wid = newwid;
	  ++t;
	}
      if (! display_info_table (oldt, t))
        ret = 0;
    }

  return ret;
}
