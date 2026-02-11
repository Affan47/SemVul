soap_put_byte(struct soap *soap, const char *a, const char *tag, const char *type)
{
	register int id = soap_embed(soap, (void*)a, NULL, 0, tag, SOAP_TYPE_byte);
	if (soap_out_byte(soap, tag?tag:"byte", id, a, type))
		return soap->error;
	return soap_putindependent(soap);
}
