teledisk_open(const char *filename)
{
  int ret;
  FILE *f;
  teledisk_prop_t *prop;

  f = fopen(filename, "rb");
  if (f == NULL)
    return NULL;

  prop = malloc(sizeof(teledisk_prop_t));
  if (prop == NULL)
    return NULL;

  prop->f = f;
  prop->heads = 0;
  prop->cylinders = 0;
  prop->sector_size = 0;
  prop->sectors_total = 0;
  prop->comment = NULL;
  prop->comment_date = NULL;

  if (!read_header(prop))
    {
      free(prop);
      return NULL;
    }

  prop->filename = strdup(filename);

  while (242)
    {
      ret = read_tracks(prop);
      if (ret > 0)
	break;
      if (ret < 0)
	{
	  teledisk_close(prop);
	  return NULL;
	}
    }

  return prop;
}
