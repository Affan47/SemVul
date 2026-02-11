soap_outint(struct soap *soap, const char *tag, int id, const int *p, const char *type, int n)
{ if (soap_element_begin_out(soap, tag, soap_embedded_id(soap, id, p, n), type)
   || soap_string_out(soap, soap_long2s(soap, (long)*p), 0))
    return soap->error;
  return soap_element_end_out(soap, tag);
}
