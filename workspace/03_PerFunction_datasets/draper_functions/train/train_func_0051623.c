soap_wsa_set_error(struct soap *soap, const char **c, const char **s)
{ struct soap_wsa_data *data = (struct soap_wsa_data*)soap_lookup_plugin(soap, soap_wsa_id);
  DBGFUN("soap_wsa_set_error");
  if (!data)
    return;
  if (data->fseterror)
    data->fseterror(soap, c, s);
  if (soap->error == SOAP_NO_METHOD || (soap->error == SOAP_TAG_MISMATCH && soap->level == 2))
  {
#if defined(SOAP_WSA_2005)
    soap->error = soap_wsa_error(soap, SOAP_WSA(ActionNotSupported), soap->action);
#elif defined(SOAP_WSA_2003)
    soap->error = soap_wsa_error(soap, "Action not supported");
#else
    soap->error = soap_wsa_error(soap, SOAP_WSA(ActionNotSupported));
#endif
  }
}
