soap_wsse_sign_only(struct soap *soap, const char *tags)
{ struct soap_wsse_data *data = (struct soap_wsse_data*)soap_lookup_plugin(soap, soap_wsse_id);
  DBGFUN1("soap_wsse_sign_only", "tags=%s", tags?tags:"(null)");
  if (data)
    data->sigid = soap_wsse_ids(soap, tags);
  return SOAP_OK;
}
