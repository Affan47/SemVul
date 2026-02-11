soap_s2wsa5__FaultCodesType(struct soap *soap, const char *s, enum wsa5__FaultCodesType *a)
{
	const struct soap_code_map *map;
	char *t;
	if (!s)
		return soap->error;
	soap_s2QName(soap, s, &t, 0, -1);
	map = soap_code(soap_codes_wsa5__FaultCodesType, t);
	if (map)
		*a = (enum wsa5__FaultCodesType)map->code;
	else
	{	long n;
		if (soap_s2long(soap, s, &n) || ((soap->mode & SOAP_XML_STRICT) && (n < 0 || n > 10)))
			return soap->error = SOAP_TYPE;
		*a = (enum wsa5__FaultCodesType)n;
	}
	return SOAP_OK;
}
