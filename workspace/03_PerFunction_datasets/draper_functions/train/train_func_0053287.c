soap_in_std__vectorTemplateOfPointerToa__address(struct soap *soap, const char *tag, std::vector<a__address * >*a, const char *type)
{
	(void)type;
	short soap_flag;
	for (soap_flag = 0;; soap_flag = 1)
	{	a__address *n;
		if (tag && *tag != '-')
		{	if (soap_element_begin_in(soap, tag, 1, NULL))
				break;
			soap_revert(soap);
		}
		n = NULL;
		if (tag && *tag != '-' && (*soap->id || *soap->href))
		{	if (!soap_container_id_forward(soap, *soap->id?soap->id:soap->href, a, (size_t)a->size(), SOAP_TYPE_a__address, SOAP_TYPE_std__vectorTemplateOfPointerToa__address, sizeof(a__address), 1))
				break;
			if (!soap_in_PointerToa__address(soap, tag, NULL, "a:address"))
				break;
		}
		else if (!soap_in_PointerToa__address(soap, tag, &n, "a:address"))
			break;
		if (!a && !(a = soap_new_std__vectorTemplateOfPointerToa__address(soap, -1)))
			return NULL;
		a->push_back(n);
		if (!tag || *tag == '-')
			return a;
	}
	if (soap_flag && (soap->error == SOAP_TAG_MISMATCH || soap->error == SOAP_NO_TAG))
	{	soap->error = SOAP_OK;
		return a;
	}
	return NULL;
}
