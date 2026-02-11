soap_out_m__PutDataResponse(struct soap *soap, const char *tag, int id, const struct m__PutDataResponse *a, const char *type)
{
	(void)soap; (void)tag; (void)id; (void)type;
	if (soap_element_begin_out(soap, tag, soap_embedded_id(soap, id, a, SOAP_TYPE_m__PutDataResponse), type))
		return soap->error;
	soap_element_result(soap, "x:keys");
	if (soap_out_x__Keys(soap, "x:keys", -1, &a->x__keys, ""))
		return soap->error;
	return soap_element_end_out(soap, tag);
}
