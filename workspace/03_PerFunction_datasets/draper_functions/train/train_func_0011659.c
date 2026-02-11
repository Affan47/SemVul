soap_wsa_alloc_header(struct soap *soap)
{ soap_header(soap);
  if (soap->header)
    return SOAP_OK;
  return soap->error = SOAP_EOM;
}
