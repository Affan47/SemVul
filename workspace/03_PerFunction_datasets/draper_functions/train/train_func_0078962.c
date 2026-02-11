soap_serve_ns5__put(struct soap *soap)
{	struct ns5__put soap_tmp_ns5__put;
	struct ns5__putResponse _param_1;
	soap_default_ns5__putResponse(soap, &_param_1);
	soap_default_ns5__put(soap, &soap_tmp_ns5__put);
	if (!soap_get_ns5__put(soap, &soap_tmp_ns5__put, "ns5:put", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns5__put(soap, soap_tmp_ns5__put._arg0, soap_tmp_ns5__put._arg1, soap_tmp_ns5__put._arg2, soap_tmp_ns5__put._arg3, soap_tmp_ns5__put._arg4, &_param_1);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = "http://schemas.xmlsoap.org/soap/encoding/";
	soap_serializeheader(soap);
	soap_serialize_ns5__putResponse(soap, &_param_1);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns5__putResponse(soap, &_param_1, "ns5:putResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns5__putResponse(soap, &_param_1, "ns5:putResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}
