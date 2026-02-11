check_printer_state(
    http_t      *http,
    const char  *uri,
    const char  *resource,
    const char  *user,
    int         version,
    int         job_id)
{
  ipp_t	*request,
	*response;
  static const char * const attrs[] =
  {
    "com.apple.print.recoverable-message",
    "marker-colors",
    "marker-levels",
    "marker-message",
    "marker-names",
    "marker-types",
    "printer-state-message",
    "printer-state-reasons"
  };


  request = ippNewRequest(IPP_GET_PRINTER_ATTRIBUTES);
  request->request.op.version[0] = version / 10;
  request->request.op.version[1] = version % 10;

  ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_URI, "printer-uri",
               NULL, uri);

  if (user && user[0])
    ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_NAME,
                 "requesting-user-name", NULL, user);

  ippAddStrings(request, IPP_TAG_OPERATION, IPP_TAG_KEYWORD,
                "requested-attributes",
		(int)(sizeof(attrs) / sizeof(attrs[0])), NULL, attrs);


  if (http->version < HTTP_1_1)
    httpReconnect(http);

  if ((response = cupsDoRequest(http, request, resource)) != NULL)
  {
    report_printer_state(response, job_id);
    ippDelete(response);
  }
}
