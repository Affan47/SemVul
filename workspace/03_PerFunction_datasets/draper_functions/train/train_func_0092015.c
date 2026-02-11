cupsGetResponse(http_t     *http,
                const char *resource)
{
  http_status_t	status;
  ipp_state_t	state;
  ipp_t		*response = NULL;


  DEBUG_printf(("cupsGetResponse(http=%p, resource=\"%s\")", http, resource));


  if (!http)
    http = _cupsConnect();

  if (!http || (http->state != HTTP_STATE_POST_RECV &&
                http->state != HTTP_STATE_POST_SEND))
    return (NULL);


  if (http->data_encoding == HTTP_ENCODING_CHUNKED)
  {


    DEBUG_puts("2cupsGetResponse: Finishing chunked POST...");

    if (httpWrite2(http, "", 0) < 0)
      return (NULL);
  }


  DEBUG_printf(("2cupsGetResponse: Update loop, http->status=%d...",
                http->status));

  do
  {
    status = httpUpdate(http);
  }
  while (status == HTTP_STATUS_CONTINUE);

  DEBUG_printf(("2cupsGetResponse: status=%d", status));

  if (status == HTTP_STATUS_OK)
  {


    response = ippNew();

    while ((state = ippRead(http, response)) != IPP_STATE_DATA)
      if (state == IPP_STATE_ERROR)
	break;

    if (state == IPP_STATE_ERROR)
    {


      DEBUG_puts("1cupsGetResponse: IPP read error!");

      httpFlush(http);

      ippDelete(response);
      response = NULL;

      http->status = status = HTTP_STATUS_ERROR;
      http->error  = EINVAL;
    }
  }
  else if (status != HTTP_STATUS_ERROR)
  {


    httpFlush(http);


    if (status == HTTP_STATUS_UNAUTHORIZED)
    {


      DEBUG_puts("2cupsGetResponse: Need authorization...");

      if (!cupsDoAuthentication(http, "POST", resource))
        httpReconnect2(http, 30000, NULL);
      else
        http->status = status = HTTP_STATUS_CUPS_AUTHORIZATION_CANCELED;
    }

#ifdef HAVE_SSL
    else if (status == HTTP_STATUS_UPGRADE_REQUIRED)
    {


      DEBUG_puts("2cupsGetResponse: Need encryption...");

      if (!httpReconnect2(http, 30000, NULL))
        httpEncryption(http, HTTP_ENCRYPTION_REQUIRED);
    }
#endif
  }

  if (response)
  {
    ipp_attribute_t	*attr;


    attr = ippFindAttribute(response, "status-message", IPP_TAG_TEXT);

    DEBUG_printf(("1cupsGetResponse: status-code=%s, status-message=\"%s\"",
                  ippErrorString(response->request.status.status_code),
                  attr ? attr->values[0].string.text : ""));

    _cupsSetError(response->request.status.status_code,
                  attr ? attr->values[0].string.text :
		      ippErrorString(response->request.status.status_code), 0);
  }

  return (response);
}
