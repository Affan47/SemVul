create_job(http_t        *http,
           const char    *dest,
	   const char    *title,
	   const char    *docname,
           const char    *user,
	   int           num_options,
	   cups_option_t *options)
{
  ipp_t		*request;
  ipp_t		*response;
  ipp_attribute_t *attr;
  char		uri[HTTP_MAX_URI];
  int		id;


  request = ippNewRequest(IPP_CREATE_JOB);

  httpAssembleURIf(HTTP_URI_CODING_ALL, uri, sizeof(uri), "ipp", NULL,
                   "localhost", 0, "/printers/%s", dest);

  ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_URI, "printer-uri",
               NULL, uri);

  ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_NAME,
               "requesting-user-name", NULL, user);

  if (title[0])
    ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_NAME, "job-name",
                 NULL, title);

  if (docname[0])
    ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_NAME, "document-name",
                 NULL, docname);

  cupsEncodeOptions(request, num_options, options);


  snprintf(uri, sizeof(uri), "/printers/%s", dest);

  response = cupsDoRequest(http, request, uri);

  if (!response || cupsLastError() > IPP_OK_CONFLICT)
  {
    syslog(LOG_ERR, "Unable to create job - %s", cupsLastErrorString());

    ippDelete(response);

    return (-1);
  }


  if ((attr = ippFindAttribute(response, "job-id", IPP_TAG_INTEGER)) == NULL)
  {
    id = -1;

    syslog(LOG_ERR, "No job-id attribute found in response from server!");
  }
  else
  {
    id = attr->values[0].integer;

    syslog(LOG_INFO, "Print file - job ID = %d", id);
  }

  ippDelete(response);

  return (id);
}
