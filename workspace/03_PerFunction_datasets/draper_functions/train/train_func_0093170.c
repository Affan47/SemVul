soap_serve_request(struct soap *soap)
{
	soap_peek_element(soap);
	if (!soap_match_tag(soap, soap->tag, "ns1:add"))
		return soap_serve_ns1__add(soap);
	if (!soap_match_tag(soap, soap->tag, "ns1:sub"))
		return soap_serve_ns1__sub(soap);
	if (!soap_match_tag(soap, soap->tag, "ns1:mul"))
		return soap_serve_ns1__mul(soap);
	if (!soap_match_tag(soap, soap->tag, "ns1:div"))
		return soap_serve_ns1__div(soap);
	return soap->error = SOAP_NO_METHOD;
}
