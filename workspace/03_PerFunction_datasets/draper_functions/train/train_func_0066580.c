do_set_default(http_t *http)
{
  const char	*title;
  ipp_t		*request;
  char		uri[HTTP_MAX_URI];
  const char	*printer,
		*is_class;


  is_class = cgiGetVariable("IS_CLASS");
  printer  = cgiGetVariable("PRINTER_NAME");
  title    = cgiText(_("Set As Server Default"));

  if (!printer)
  {
    cgiSetVariable("ERROR", cgiText(_("Missing form variable")));
    cgiStartHTML(title);
    cgiCopyTemplateLang("error.tmpl");
    cgiEndHTML();
    return;
  }


  request = ippNewRequest(CUPS_SET_DEFAULT);

  httpAssembleURIf(HTTP_URI_CODING_ALL, uri, sizeof(uri), "ipp", NULL,
                   "localhost", 0, is_class ? "/classes/%s" : "/printers/%s",
		   printer);
  ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_URI, "printer-uri",
               NULL, uri);


  ippDelete(cupsDoRequest(http, request, "/admin/"));

  if (cupsLastError() == IPP_NOT_AUTHORIZED)
  {
    puts("Status: 401\n");
    exit(0);
  }
  else if (cupsLastError() > IPP_OK_CONFLICT)
  {
    cgiStartHTML(title);
    cgiShowIPPError(_("Unable to set server default"));
  }
  else
  {


    char	url[1024],
		refresh[1024];


    cgiRewriteURL(uri, url, sizeof(url), NULL);
    cgiFormEncode(uri, url, sizeof(uri));
    snprintf(refresh, sizeof(refresh), "5;URL=/admin/?OP=redirect&URL=%s", uri);
    cgiSetVariable("refresh_page", refresh);

    cgiStartHTML(title);
    cgiCopyTemplateLang("printer-default.tmpl");
  }

  cgiEndHTML();
}
