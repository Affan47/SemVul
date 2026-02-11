compute_level_full_list (void)
{
  int i;
  unsigned int j;

  dmsg (D_SECTION, "compute level full list");

  level_full_list_size = level_list_size + extra_nbr;
  XMALLOC_ARRAY (level_full_list, level_full_list_size);

  if (extra_nbr == 0) {
    extrasel = 0;
    opt.extras = 0;
  }
  if (extrasel) {
    i = extra_nbr - 1;
    while ((i >= 0) && extra_selected_list[i] == 0)
      i--;
    if (i < 0)
      opt.extras = 0;
  }
  i = 0;
  if (opt.extras != 2)
    for (; i < (int) level_list_size; i++)
      level_full_list[i] = i;
  if (opt.extras != 0)
    for (j = 0; j < extra_nbr; j++)
      if (extra_selected_list[j] || (extrasel == 0))
	level_full_list[i++] = (j | 0x10000);
  level_full_list_size = i;
}
