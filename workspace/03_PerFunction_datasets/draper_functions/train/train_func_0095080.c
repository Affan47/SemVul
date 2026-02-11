stp_path_split(stp_list_t *list,
	       const char *path)
{
  const char *start = path;
  const char *end = NULL;
  char *dir = NULL;
  int len;

  while (start)
    {
      end = (const char *) strchr(start, ':');
      if (!end)
	len = strlen(start) + 1;
      else
	len = (end - start);

      if (len && !(len == 1 && !end))
	{
	  dir = (char *) stp_malloc(len + 1);
	  strncpy(dir, start, len);
	  dir[len] = '\0';
	  stp_list_item_create(list, NULL, dir);
	}
      if (!end)
	{
	  start = NULL;
	  break;
	}
      start = end + 1;
    }
}
