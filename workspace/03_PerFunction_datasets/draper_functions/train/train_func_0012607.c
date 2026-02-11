soap_out_ns__Square(struct soap *soap, const char *tag, int id, const ns__Square *a, const char *type)
{
	if (soap_element_begin_out(soap, tag, soap_embedded_id(soap, id, a, SOAP_TYPE_ns__Square), "ns:Square"))
		return soap->error;
	if (soap_out_string(soap, "name", -1, &(a->ns__Object::name), ""))
		return soap->error;


	if (soap_out_string(soap, "name", -1, &(a->ns__Shape::name), ""))
		return soap->error;
	if (soap_out_int(soap, "sides", -1, &(a->ns__Shape::sides), ""))
		return soap->error;


	if (soap_out_string(soap, "name", -1, &(a->ns__Square::name), ""))
		return soap->error;

	if (soap_out_int(soap, "size", -1, &(a->ns__Square::size), ""))
		return soap->error;


	return soap_element_end_out(soap, tag);
}
