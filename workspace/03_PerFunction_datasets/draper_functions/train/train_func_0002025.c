soap_in_methodResponse(struct soap *soap, const char *tag, struct methodResponse *a, const char *type)
{
	size_t soap_flag_params = 1;
	size_t soap_flag_fault = 1;
	if (soap_element_begin_in(soap, tag, 0, type))
		return NULL;
	a = (struct methodResponse *)soap_id_enter(soap, soap->id, a, SOAP_TYPE_methodResponse, sizeof(struct methodResponse), 0, NULL, NULL, NULL);
	if (!a)
		return NULL;
	soap_default_methodResponse(soap, a);
	if (soap->body && !*soap->href)
	{
		for (;;)
		{	soap->error = SOAP_TAG_MISMATCH;


			if (soap_flag_params && soap->error == SOAP_TAG_MISMATCH)
				if (soap_in_PointerToparams(soap, "params", &a->params, "params"))
				{	soap_flag_params--;
					continue;
				}
			if (soap_flag_fault && soap->error == SOAP_TAG_MISMATCH)
				if (soap_in_PointerTofault(soap, "fault", &a->fault, "fault"))
				{	soap_flag_fault--;
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
	{	a = (struct methodResponse *)soap_id_forward(soap, soap->href, (void*)a, 0, SOAP_TYPE_methodResponse, 0, sizeof(struct methodResponse), 0, NULL);
		if (soap->body && soap_element_end_in(soap, tag))
			return NULL;
	}
	return a;
}
