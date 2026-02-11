soap_body_begin_in(struct soap *soap)
{ soap->part = SOAP_IN_BODY;
  if (soap_element_begin_in(soap, "SOAP-ENV:Body", 0, NULL))
    return soap->error;
  if (!soap->body)
    soap->part = SOAP_NO_BODY;
  return SOAP_OK;
}
