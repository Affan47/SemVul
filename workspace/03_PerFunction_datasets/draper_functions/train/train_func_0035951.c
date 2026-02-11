soap_out_vector(struct soap *soap, const char *tag, int id, const vector *a, const char *type)
{
	int i, n = a->__size;
	char *t = a->__ptr ? soap_putsize(soap, "xsd:double", n + a->__offset) : NULL;
	id = soap_element_id(soap, tag, id, a, (struct soap_array*)&a->__ptr, 1, type, SOAP_TYPE_vector);
	if (id < 0)
		return soap->error;
	if (soap_array_begin_out(soap, tag, id, t, soap_putoffset(soap, a->__offset)))
		return soap->error;
	for (i = 0; i < n; i++)
	{
		soap->position = 1;
		soap->positions[0] = i;
		soap_out_xsd__double(soap, "item", -1, &a->__ptr[i], "");
	}
	soap->position = 0;
	return soap_element_end_out(soap, tag);
}
