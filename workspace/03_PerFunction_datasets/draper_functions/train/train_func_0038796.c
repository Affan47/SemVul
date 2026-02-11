soap_out_PointerTounsignedByte(struct soap *soap, const char *tag, int id, unsigned char *const*a, const char *type)
{
	id = soap_element_id(soap, tag, id, *a, NULL, 0, type, SOAP_TYPE_unsignedByte);
	if (id < 0)
		return soap->error;
	return soap_out_unsignedByte(soap, tag, id, *a, type);
}
