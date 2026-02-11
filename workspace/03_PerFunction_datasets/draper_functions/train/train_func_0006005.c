soap_out_t__object(struct soap *soap, const char *tag, int id, const enum t__object *a, const char *type)
{	if (soap_element_begin_out(soap, tag, soap_embedded_id(soap, id, a, SOAP_TYPE_t__object), type) || soap_send(soap, soap_t__object2s(soap, *a)))
		return soap->error;
	return soap_element_end_out(soap, tag);
}
