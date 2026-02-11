soap_in_wsa5__MetadataType(struct soap *soap, const char *tag, struct wsa5__MetadataType *a, const char *type)
{
	struct soap_blist *soap_blist___any = NULL;
	if (soap_element_begin_in(soap, tag, 0, type))
		return NULL;
	a = (struct wsa5__MetadataType *)soap_id_enter(soap, soap->id, a, SOAP_TYPE_wsa5__MetadataType, sizeof(struct wsa5__MetadataType), 0, NULL, NULL, NULL);
	if (!a)
		return NULL;
	soap_default_wsa5__MetadataType(soap, a);
	if (soap_s2string(soap, soap_attr_value(soap, "-anyAttribute", 0), &a->__anyAttribute, 0, -1))
		return NULL;
	if (soap->body && !*soap->href)
	{
		for (;;)
		{	soap->error = SOAP_TAG_MISMATCH;
			if (soap->error == SOAP_TAG_MISMATCH && !soap_peek_element(soap))
			{	if (a->__any == NULL)
				{	if (soap_blist___any == NULL)
						soap_blist___any = soap_new_block(soap);
					a->__any = (char **)soap_push_block(soap, soap_blist___any, sizeof(char *));
					if (a->__any == NULL)
						return NULL;
					*a->__any = NULL;
				}
				if (soap_inliteral(soap, "-any", a->__any))
				{	a->__size++;
					a->__any = NULL;
					continue;
				}
			}
			if (soap->error == SOAP_TAG_MISMATCH)
				soap->error = soap_ignore_element(soap);
			if (soap->error == SOAP_NO_TAG)
				break;
			if (soap->error)
				return NULL;
		}
		if (a->__any)
			soap_pop_block(soap, soap_blist___any);
		if (a->__size)
			a->__any = (char **)soap_save_block(soap, soap_blist___any, NULL, 1);
		else
		{	a->__any = NULL;
			if (soap_blist___any)
				soap_end_block(soap, soap_blist___any);
		}
		if (soap_element_end_in(soap, tag))
			return NULL;
	}
	else
	{	a = (struct wsa5__MetadataType *)soap_id_forward(soap, soap->href, (void*)a, 0, SOAP_TYPE_wsa5__MetadataType, 0, sizeof(struct wsa5__MetadataType), 0, NULL);
		if (soap->body && soap_element_end_in(soap, tag))
			return NULL;
	}
	return a;
}
