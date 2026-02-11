soap_markelement(struct soap *soap, const void *ptr, int type)
{
	(void)soap; (void)ptr; (void)type;
	switch (type)
	{
	case SOAP_TYPE_r__roll:
		soap_serialize_r__roll(soap, (const struct r__roll *)ptr);
		break;
	case SOAP_TYPE_r__rollResponse:
		soap_serialize_r__rollResponse(soap, (const struct r__rollResponse *)ptr);
		break;
	case SOAP_TYPE__QName:
		soap_serialize_string(soap, (char*const*)&ptr);
		break;
	case SOAP_TYPE_string:
		soap_serialize_string(soap, (char*const*)&ptr);
		break;
	}
}
