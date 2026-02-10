parse_option (int key, char *arg, struct argp_state *state)
{
  char *endp;
  switch (key)
    {
    case 's':
      endp = strchr (arg, ':');
      if (endp == NULL)

	for (int i = 0; databases[i].name != NULL; ++i)
	  __nss_configure_lookup (databases[i].name, arg);
      else
	{
	  int i;
	  for (i = 0; databases[i].name != NULL; ++i)
	    if (strncmp (databases[i].name, arg, endp - arg) == 0)
	      {
		__nss_configure_lookup (databases[i].name, endp + 1);
		break;
	      }
	  if (databases[i].name == NULL)
	    error (EXIT_FAILURE, 0, gettext ("Unknown database name"));
	}
      break;

    case 'i':
      idn_flags = 0;
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }

  return 0;
}
