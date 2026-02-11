soap_s2t__object(struct soap *soap, const char *s, enum t__object *a)
{
	const struct soap_code_map *map;
	if (!s)
		return soap->error;
	map = soap_code(soap_codes_t__object, s);
	if (map)
		*a = (enum t__object)map->code;
	else
	{	long n;
		if (soap_s2long(soap, s, &n) || ((soap->mode & SOAP_XML_STRICT) && (n < 0 || n > 2)))
			return soap->error = SOAP_TYPE;
		*a = (enum t__object)n;
	}
	return SOAP_OK;
}
