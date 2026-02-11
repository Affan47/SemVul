soap_in_ns__wsrmdemoResponse(struct soap *soap, const char *tag, struct ns__wsrmdemoResponse *a, const char *type)
{
	size_t soap_flag_out = 1;
	if (soap_element_begin_in(soap, tag, 0, type))
		return NULL;
	a = (struct ns__wsrmdemoResponse *)soap_id_enter(soap, soap->id, a, SOAP_TYPE_ns__wsrmdemoResponse, sizeof(struct ns__wsrmdemoResponse), 0, NULL, NULL, NULL);
	if (!a)
		return NULL;
	soap_default_ns__wsrmdemoResponse(soap, a);
	if (soap->body && !*soap->href)
	{
		for (;;)
		{	soap->error = SOAP_TAG_MISMATCH;
			if (soap_flag_out && (soap->error == SOAP_TAG_MISMATCH || soap->error == SOAP_NO_TAG))
				if (soap_in_string(soap, "out", &a->out, "xsd:string"))
				{	soap_flag_out--;
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
	{	a = (struct ns__wsrmdemoResponse *)soap_id_forward(soap, soap->href, (void*)a, 0, SOAP_TYPE_ns__wsrmdemoResponse, 0, sizeof(struct ns__wsrmdemoResponse), 0, NULL);
		if (soap->body && soap_element_end_in(soap, tag))
			return NULL;
	}
	return a;
}
