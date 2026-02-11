internal_gid_in_list (const gid_t *list, const gid_t g, long int len)
{
  while (len > 0)
    {
      if (*list == g)
	return 1;
      --len;
      ++list;
    }
  return 0;
}
