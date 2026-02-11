soap_serve_t__gmt(struct soap *soap)
{	struct t__gmt soap_tmp_t__gmt;
	struct t__gmtResponse soap_tmp_t__gmtResponse;
	time_t soap_tmp_time;
	soap_default_t__gmtResponse(soap, &soap_tmp_t__gmtResponse);
	soap_default_time(soap, &soap_tmp_time);
	soap_tmp_t__gmtResponse._param_1 = &soap_tmp_time;
	soap_default_t__gmt(soap, &soap_tmp_t__gmt);
	if (!soap_get_t__gmt(soap, &soap_tmp_t__gmt, "t:gmt", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = t__gmt(soap, soap_tmp_t__gmtResponse._param_1);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_t__gmtResponse(soap, &soap_tmp_t__gmtResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_t__gmtResponse(soap, &soap_tmp_t__gmtResponse, "t:gmtResponse", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_t__gmtResponse(soap, &soap_tmp_t__gmtResponse, "t:gmtResponse", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}
