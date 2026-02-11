soap_serve_ns1__lusols(struct soap *soap)
{	struct ns1__lusols soap_tmp_ns1__lusols;
	struct ns1__lusolsResponse soap_tmp_ns1__lusolsResponse;
	matrix soap_tmp_matrix;
	soap_default_ns1__lusolsResponse(soap, &soap_tmp_ns1__lusolsResponse);
	soap_tmp_matrix.soap_default(soap);
	soap_tmp_ns1__lusolsResponse.x = &soap_tmp_matrix;
	soap_default_ns1__lusols(soap, &soap_tmp_ns1__lusols);
	if (!soap_get_ns1__lusols(soap, &soap_tmp_ns1__lusols, "ns1:lusols", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns1__lusols(soap, soap_tmp_ns1__lusols.a, soap_tmp_ns1__lusols.b, soap_tmp_ns1__lusolsResponse.x);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = "";
	soap_serializeheader(soap);
	soap_serialize_ns1__lusolsResponse(soap, &soap_tmp_ns1__lusolsResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns1__lusolsResponse(soap, &soap_tmp_ns1__lusolsResponse, "ns1:lusolsResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns1__lusolsResponse(soap, &soap_tmp_ns1__lusolsResponse, "ns1:lusolsResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}
