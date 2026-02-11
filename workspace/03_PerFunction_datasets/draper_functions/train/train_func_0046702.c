soap_serve_ns__create(struct soap *soap)
{	struct ns__create soap_tmp_ns__create;
	struct ns__createResponse soap_tmp_ns__createResponse;
	soap_default_ns__createResponse(soap, &soap_tmp_ns__createResponse);
	soap_default_ns__create(soap, &soap_tmp_ns__create);
	if (!soap_get_ns__create(soap, &soap_tmp_ns__create, "ns:create", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__create(soap, soap_tmp_ns__create.object, soap_tmp_ns__create.name, soap_tmp_ns__createResponse.status);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = "";
	soap_serializeheader(soap);
	soap_serialize_ns__createResponse(soap, &soap_tmp_ns__createResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__createResponse(soap, &soap_tmp_ns__createResponse, "ns:createResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__createResponse(soap, &soap_tmp_ns__createResponse, "ns:createResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}
