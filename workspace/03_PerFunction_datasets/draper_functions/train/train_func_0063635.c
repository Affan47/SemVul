soap_in_ds__KeyInfoType(struct soap *soap, const char *tag, struct ds__KeyInfoType *a, const char *type)
{
	size_t soap_flag_KeyName = 1;
	size_t soap_flag_KeyValue = 1;
	size_t soap_flag_RetrievalMethod = 1;
	size_t soap_flag_X509Data = 1;
	size_t soap_flag_wsse__SecurityTokenReference = 1;
	if (soap_element_begin_in(soap, tag, 0, type))
		return NULL;
	a = (struct ds__KeyInfoType *)soap_id_enter(soap, soap->id, a, SOAP_TYPE_ds__KeyInfoType, sizeof(struct ds__KeyInfoType), 0, NULL, NULL, NULL);
	if (!a)
		return NULL;
	soap_default_ds__KeyInfoType(soap, a);
	if (soap_s2string(soap, soap_attr_value(soap, "Id", 0), &a->Id, 0, -1))
		return NULL;
	if (soap->body && !*soap->href)
	{
		for (;;)
		{	soap->error = SOAP_TAG_MISMATCH;
			if (soap_flag_KeyName && (soap->error == SOAP_TAG_MISMATCH || soap->error == SOAP_NO_TAG))
				if (soap_in_string(soap, "ds:KeyName", &a->KeyName, "xsd:string"))
				{	soap_flag_KeyName--;
					continue;
				}
			if (soap_flag_KeyValue && soap->error == SOAP_TAG_MISMATCH)
				if (soap_in_PointerTods__KeyValueType(soap, "ds:KeyValue", &a->KeyValue, "ds:KeyValueType"))
				{	soap_flag_KeyValue--;
					continue;
				}
			if (soap_flag_RetrievalMethod && soap->error == SOAP_TAG_MISMATCH)
				if (soap_in_PointerTods__RetrievalMethodType(soap, "ds:RetrievalMethod", &a->RetrievalMethod, "ds:RetrievalMethodType"))
				{	soap_flag_RetrievalMethod--;
					continue;
				}
			if (soap_flag_X509Data && soap->error == SOAP_TAG_MISMATCH)
				if (soap_in_PointerTods__X509DataType(soap, "ds:X509Data", &a->X509Data, "ds:X509DataType"))
				{	soap_flag_X509Data--;
					continue;
				}
			if (soap_flag_wsse__SecurityTokenReference && soap->error == SOAP_TAG_MISMATCH)
				if (soap_in_PointerTo_wsse__SecurityTokenReference(soap, "wsse:SecurityTokenReference", &a->wsse__SecurityTokenReference, ""))
				{	soap_flag_wsse__SecurityTokenReference--;
					continue;
				}
			if (soap->error == SOAP_TAG_MISMATCH)
				soap->error = soap_ignore_element(soap);
			if (soap->error == SOAP_NO_TAG)
				break;
			if (soap->error)
				return NULL;
		}
		if (soap_element_end_in(soap, tag))
			return NULL;
	}
	else
	{	a = (struct ds__KeyInfoType *)soap_id_forward(soap, soap->href, (void*)a, 0, SOAP_TYPE_ds__KeyInfoType, 0, sizeof(struct ds__KeyInfoType), 0, NULL);
		if (soap->body && soap_element_end_in(soap, tag))
			return NULL;
	}
	return a;
}
