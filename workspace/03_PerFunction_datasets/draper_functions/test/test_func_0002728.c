soap_wsse_add_Security(struct soap *soap)
{ DBGFUN("soap_wsse_add_Security");

  soap_header(soap);

  if (!soap->header->wsse__Security)
  { soap->header->wsse__Security = (_wsse__Security*)soap_malloc(soap, sizeof(_wsse__Security));
    if (!soap->header->wsse__Security)
      return NULL;
    soap_default__wsse__Security(soap, soap->header->wsse__Security);
  }
  return soap->header->wsse__Security;
}
