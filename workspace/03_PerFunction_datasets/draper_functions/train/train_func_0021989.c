free_level_list (void)
{
  size_t i;
  for (i = 0; i < level_list_size; ++i)
    free (level_list[i].name);
  free (level_list);
  level_list = 0;
  level_list_max = 0;
  level_list_size = 0;
}
