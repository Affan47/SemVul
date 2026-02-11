soap_out_ns__mul(struct soap *soap, const char *tag, int id, const struct ns__mul *a, const char *type)
{
	(void)soap; (void)tag; (void)id; (void)type;
	if (soap_element_begin_out(soap, tag, soap_embedded_id(soap, id, a, SOAP_TYPE_Calc_ns__mul), type))
		return soap->error;
	if (soap_out_double(soap, "a", -1, &a->a, ""))
		return soap->error;
	if (soap_out_double(soap, "b", -1, &a->b, ""))
		return soap->error;
	return soap_element_end_out(soap, tag);
}
