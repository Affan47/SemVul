soap_serve___ns4__gmt(struct soap *soap)
{	struct __ns4__gmt soap_tmp___ns4__gmt;
	struct _ns1__gmtResponse ns1__gmtResponse;
	soap_default__ns1__gmtResponse(soap, &ns1__gmtResponse);
	soap_default___ns4__gmt(soap, &soap_tmp___ns4__gmt);
	if (!soap_get___ns4__gmt(soap, &soap_tmp___ns4__gmt, "-ns4:gmt", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = __ns4__gmt(soap, soap_tmp___ns4__gmt.ns1__gmt, &ns1__gmtResponse);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize__ns1__gmtResponse(soap, &ns1__gmtResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put__ns1__gmtResponse(soap, &ns1__gmtResponse, "ns1:gmtResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put__ns1__gmtResponse(soap, &ns1__gmtResponse, "ns1:gmtResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}
