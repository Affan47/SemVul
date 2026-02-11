soap_put(struct soap *soap, const char *tag, const  char *type) const
{
	register int id = soap_embed(soap, (void*)this, NULL, 0, tag, SOAP_TYPE_xsd__decimal);
	if (this->soap_out(soap, tag?tag:"xsd:decimal", id, type))
		return soap->error;
	return soap_putindependent(soap);
}
