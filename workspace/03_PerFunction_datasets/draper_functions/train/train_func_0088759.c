soap_out_wsa5__MetadataType(struct soap *soap, const char *tag, int id, const struct wsa5__MetadataType *a, const char *type)
{
	if (a->__anyAttribute)
		soap_set_attr(soap, "-anyAttribute", a->__anyAttribute, 1);
	(void)soap; (void)tag; (void)id; (void)type;
	if (soap_element_begin_out(soap, tag, soap_embedded_id(soap, id, a, SOAP_TYPE_wsa5__MetadataType), type))
		return soap->error;
	if (a->__any)
	{	int i;
		for (i = 0; i < a->__size; i++)
			soap_outliteral(soap, "-any", a->__any + i, NULL);
	}
	return soap_element_end_out(soap, tag);
}
