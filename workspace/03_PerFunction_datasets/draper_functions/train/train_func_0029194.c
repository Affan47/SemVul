soap_getelement(struct soap *soap, int *type)
{	(void)type;
	if (soap_peek_element(soap))
		return NULL;
#ifndef WITH_NOIDREF
	if (!*soap->id || !(*type = soap_lookup_type(soap, soap->id)))
		*type = soap_lookup_type(soap, soap->href);
	switch (*type)
	{
	case SOAP_TYPE_byte:
		return soap_in_byte(soap, NULL, NULL, "xsd:byte");
	case SOAP_TYPE_int:
		return soap_in_int(soap, NULL, NULL, "xsd:int");
	case SOAP_TYPE_h__hello:
		return soap_in_h__hello(soap, NULL, NULL, "h:hello");
	case SOAP_TYPE_h__helloResponse:
		return soap_in_h__helloResponse(soap, NULL, NULL, "h:helloResponse");
	case SOAP_TYPE__QName:
	{	char **s;
		s = soap_in__QName(soap, NULL, NULL, "xsd:QName");
		return s ? *s : NULL;
	}
	case SOAP_TYPE_string:
	{	char **s;
		s = soap_in_string(soap, NULL, NULL, "xsd:string");
		return s ? *s : NULL;
	}
	default:
#else
	*type = 0;
#endif
	{	const char *t = soap->type;
		if (!*t)
			t = soap->tag;
		if (!soap_match_tag(soap, t, "xsd:byte"))
		{	*type = SOAP_TYPE_byte;
			return soap_in_byte(soap, NULL, NULL, NULL);
		}
		if (!soap_match_tag(soap, t, "xsd:int"))
		{	*type = SOAP_TYPE_int;
			return soap_in_int(soap, NULL, NULL, NULL);
		}
		if (!soap_match_tag(soap, t, "h:hello"))
		{	*type = SOAP_TYPE_h__hello;
			return soap_in_h__hello(soap, NULL, NULL, NULL);
		}
		if (!soap_match_tag(soap, t, "h:helloResponse"))
		{	*type = SOAP_TYPE_h__helloResponse;
			return soap_in_h__helloResponse(soap, NULL, NULL, NULL);
		}
		if (!soap_match_tag(soap, t, "xsd:QName"))
		{	char **s;
			*type = SOAP_TYPE__QName;
			s = soap_in__QName(soap, NULL, NULL, NULL);
			return s ? *s : NULL;
		}
		if (!soap_match_tag(soap, t, "xsd:string"))
		{	char **s;
			*type = SOAP_TYPE_string;
			s = soap_in_string(soap, NULL, NULL, NULL);
			return s ? *s : NULL;
		}
		t = soap->tag;
#ifndef WITH_NOIDREF
	}
#endif
	}
	soap->error = SOAP_TAG_MISMATCH;
	return NULL;
}
