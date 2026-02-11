pl_ram_fetch (const char *const *lines, size_t index, void *data)
{

  if (lines[index][0] == '#')
    return (play_item_t *) -1;


  if (!strncasecmp (lines[index], "rtsp://", 7) ||
      !strncasecmp (lines[index], "pnm://", 6))
  {
    char line[strlen (lines[index]) + 1];
    strcpy (line, lines[index]);
    char *q = strchr (line, '?');
    if (q)
      *q = 0;
    return play_item_new (NULL, line, 0, 0);
  }
  if (!strncasecmp (lines[index], "http://", 7))
    return play_item_new (NULL, lines[index], 0, 0);

  return NULL;
}
