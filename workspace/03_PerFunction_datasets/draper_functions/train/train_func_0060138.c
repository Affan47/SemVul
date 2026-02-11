get_interface_from_argv0 (char *argv0, char *str)
{
	char *bs = strrchr (argv0, '/');

	if (bs)  argv0 = ++bs;

	if (sscanf(argv0, "alsaplayer-%s", str) == 1)  return 1;
  	if (sscanf(argv0, "jackplayer-%s", str) == 1)  return 1;

	return 0;
}
