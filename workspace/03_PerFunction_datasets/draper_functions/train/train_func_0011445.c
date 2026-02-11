check_dest(const char  *command,
           const char  *name,
           int         *num_dests,
	   cups_dest_t **dests)
{
  const char	*dptr;
  char		*pptr,
		printer[1024];


  if (*num_dests <= 1)
  {
    if (*num_dests)
      cupsFreeDests(*num_dests, *dests);

    if (strchr(name, ','))
      *num_dests = cupsGetDests(dests);
    else
    {
      strlcpy(printer, name, sizeof(printer));
      if ((pptr = strchr(printer, '/')) != NULL)
        *pptr++ = '\0';

      if ((*dests = cupsGetNamedDest(CUPS_HTTP_DEFAULT, printer, pptr)) == NULL)
      {
	if (cupsLastError() == IPP_STATUS_ERROR_BAD_REQUEST ||
	    cupsLastError() == IPP_STATUS_ERROR_VERSION_NOT_SUPPORTED)
	  _cupsLangPrintf(stderr,
			  _("%s: Error - add '/version=1.1' to server name."),
			  command);
	else
	  _cupsLangPrintf(stderr,
			  _("%s: Invalid destination name in list \"%s\"."),
			  command, name);

        exit(1);
      }
      else
      {
        *num_dests = 1;
        return;
      }
    }
  }


  for (dptr = name; *dptr;)
  {


    while (isspace(*dptr & 255) || *dptr == ',')
      dptr ++;

    if (!*dptr)
      break;


    for (pptr = printer; !isspace(*dptr & 255) && *dptr != ',' && *dptr;)
    {
      if ((pptr - printer) < (sizeof(printer) - 1))
        *pptr++ = *dptr++;
      else
      {
        _cupsLangPrintf(stderr,
	                _("%s: Invalid destination name in list \"%s\"."),
			command, name);
        exit(1);
      }
    }

    *pptr = '\0';


    if (!cupsGetDest(printer, NULL, *num_dests, *dests))
    {
      if (cupsLastError() == IPP_STATUS_ERROR_BAD_REQUEST ||
          cupsLastError() == IPP_STATUS_ERROR_VERSION_NOT_SUPPORTED)
	_cupsLangPrintf(stderr,
	                _("%s: Error - add '/version=1.1' to server name."),
			command);
      else
	_cupsLangPrintf(stderr,
			_("%s: Unknown destination \"%s\"."), command, printer);

      exit(1);
    }
  }
}
