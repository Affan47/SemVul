soap_in_ns__getImageResponse(struct soap *soap, const char *tag, struct ns__getImageResponse *a, const char *type)
{
	size_t soap_flag_image = 1;
	if (soap_element_begin_in(soap, tag, 0, type))
		return NULL;
	a = (struct ns__getImageResponse *)soap_class_id_enter(soap, soap->id, a, SOAP_TYPE_ns__getImageResponse, sizeof(struct ns__getImageResponse), soap->type, soap->arrayType);
	if (!a)
		return NULL;
	soap_default_ns__getImageResponse(soap, a);
	if (soap->body && !*soap->href)
	{
		for (;;)
		{	soap->error = SOAP_TAG_MISMATCH;
			if (soap_flag_image && soap->error == SOAP_TAG_MISMATCH)
				if (a->image.soap_in(soap, "image", "ns:Data"))
				{	soap_flag_image--;
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
	{	a = (struct ns__getImageResponse *)soap_id_forward(soap, soap->href, (void*)a, 0, SOAP_TYPE_ns__getImageResponse, 0, sizeof(struct ns__getImageResponse), 0, soap_copy_ns__getImageResponse);
		if (soap->body && soap_element_end_in(soap, tag))
			return NULL;
	}
	if ((soap->mode & SOAP_XML_STRICT) && (soap_flag_image > 0))
	{	soap->error = SOAP_OCCURS;
		return NULL;
	}
	return a;
}
