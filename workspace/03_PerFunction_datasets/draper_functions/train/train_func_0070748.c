show_printer(const char *command,
             http_t     *http,
             const char *dest)
{
  ipp_t		*request,
		*response;
  ipp_attribute_t *attr;
  ipp_pstate_t	state;
  char		uri[HTTP_MAX_URI];


  if (http == NULL)
    return;


  request = ippNewRequest(IPP_GET_PRINTER_ATTRIBUTES);

  httpAssembleURIf(HTTP_URI_CODING_ALL, uri, sizeof(uri), "ipp", NULL,
                   "localhost", 0, "/printers/%s", dest);
  ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_URI,
               "printer-uri", NULL, uri);


  if ((response = cupsDoRequest(http, request, "/")) != NULL)
  {
    if (response->request.status.status_code > IPP_OK_CONFLICT)
    {
      _cupsLangPrintf(stderr, "%s: %s", command, cupsLastErrorString());
      ippDelete(response);
      return;
    }

    if ((attr = ippFindAttribute(response, "printer-state", IPP_TAG_ENUM)) != NULL)
      state = (ipp_pstate_t)attr->values[0].integer;
    else
      state = IPP_PRINTER_STOPPED;

    switch (state)
    {
      case IPP_PRINTER_IDLE :
          _cupsLangPrintf(stdout, _("%s is ready"), dest);
	  break;
      case IPP_PRINTER_PROCESSING :
          _cupsLangPrintf(stdout, _("%s is ready and printing"),
	                  dest);
	  break;
      case IPP_PRINTER_STOPPED :
          _cupsLangPrintf(stdout, _("%s is not ready"), dest);
	  break;
    }

    ippDelete(response);
  }
  else
    _cupsLangPrintf(stderr, "%s: %s", command, cupsLastErrorString());
}
