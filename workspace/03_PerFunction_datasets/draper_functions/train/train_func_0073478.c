add_printer_to_class(http_t *http,
                     char   *printer,
		     char   *pclass)
{
  int		i;
  ipp_t		*request,
		*response;
  ipp_attribute_t *attr,
		*members;
  char		uri[HTTP_MAX_URI];


  DEBUG_printf(("add_printer_to_class(%p, \"%s\", \"%s\")\n", http,
                printer, pclass));


  request = ippNewRequest(IPP_GET_PRINTER_ATTRIBUTES);

  httpAssembleURIf(HTTP_URI_CODING_ALL, uri, sizeof(uri), "ipp", NULL,
                   "localhost", 0, "/classes/%s", pclass);
  ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_URI,
               "printer-uri", NULL, uri);
  ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_NAME, "requesting-user-name",
               NULL, cupsUser());


  response = cupsDoRequest(http, request, "/");


  request = ippNewRequest(CUPS_ADD_MODIFY_CLASS);

  ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_URI,
               "printer-uri", NULL, uri);
  ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_NAME, "requesting-user-name",
               NULL, cupsUser());


  if (response != NULL &&
      (members = ippFindAttribute(response, "member-names",
                                  IPP_TAG_NAME)) != NULL)
    for (i = 0; i < members->num_values; i ++)
      if (_cups_strcasecmp(printer, members->values[i].string.text) == 0)
      {
        _cupsLangPrintf(stderr,
	                _("lpadmin: Printer %s is already a member of class "
			  "%s."), printer, pclass);
        ippDelete(request);
	ippDelete(response);
	return (0);
      }


  httpAssembleURIf(HTTP_URI_CODING_ALL, uri, sizeof(uri), "ipp", NULL,
                   "localhost", 0, "/printers/%s", printer);

  if (response != NULL &&
      (members = ippFindAttribute(response, "member-uris",
                                  IPP_TAG_URI)) != NULL)
  {


    attr = ippAddStrings(request, IPP_TAG_PRINTER, IPP_TAG_URI,
                         "member-uris", members->num_values + 1, NULL, NULL);
    for (i = 0; i < members->num_values; i ++)
      attr->values[i].string.text =
          _cupsStrAlloc(members->values[i].string.text);

    attr->values[i].string.text = _cupsStrAlloc(uri);
  }
  else
    ippAddString(request, IPP_TAG_PRINTER, IPP_TAG_URI, "member-uris", NULL,
                 uri);


  ippDelete(response);

  ippDelete(cupsDoRequest(http, request, "/admin/"));
  if (cupsLastError() > IPP_OK_CONFLICT)
  {
    _cupsLangPrintf(stderr, _("%s: %s"), "lpadmin", cupsLastErrorString());

    return (1);
  }
  else
    return (0);
}
