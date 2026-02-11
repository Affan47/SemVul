soap_markelement(struct soap *soap, const void *ptr, int type)
{
	(void)soap; (void)ptr; (void)type;
	switch (type)
	{
	case SOAP_TYPE_rss:
		soap_serialize_rss(soap, (const struct rss *)ptr);
		break;
	case SOAP_TYPE_item:
		soap_serialize_item(soap, (const struct item *)ptr);
		break;
	case SOAP_TYPE_image:
		soap_serialize_image(soap, (const struct image *)ptr);
		break;
	case SOAP_TYPE_channel:
		soap_serialize_channel(soap, (const struct channel *)ptr);
		break;
	case SOAP_TYPE_PointerTotime:
		soap_serialize_PointerTotime(soap, (time_t *const*)ptr);
		break;
	case SOAP_TYPE_PointerToitem:
		soap_serialize_PointerToitem(soap, (struct item *const*)ptr);
		break;
	case SOAP_TYPE_PointerToimage:
		soap_serialize_PointerToimage(soap, (struct image *const*)ptr);
		break;
	case SOAP_TYPE__QName:
		soap_serialize_string(soap, (char*const*)&ptr);
		break;
	case SOAP_TYPE_string:
		soap_serialize_string(soap, (char*const*)&ptr);
		break;
	}
}
