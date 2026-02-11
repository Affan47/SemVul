soap_serialize__wsc__union_DerivedKeyTokenType(struct soap *soap, int choice, const union _wsc__union_DerivedKeyTokenType *a)
{
#ifndef WITH_NOIDREF
	(void)soap; (void)a;
	switch (choice)
	{
	case SOAP_UNION__wsc__union_DerivedKeyTokenType_Generation:
		soap_embedded(soap, &a->Generation, SOAP_TYPE_unsignedLONG64);
		break;
	case SOAP_UNION__wsc__union_DerivedKeyTokenType_Offset:
		soap_embedded(soap, &a->Offset, SOAP_TYPE_unsignedLONG64);
		break;
	default:
		break;
	}
#endif
}
