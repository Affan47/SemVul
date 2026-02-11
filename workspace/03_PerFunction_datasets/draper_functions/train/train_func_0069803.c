soap_call_t__gmt(struct soap *soap, const char *soap_endpoint, const char *soap_action, time_t *_param_1)
{	struct t__gmt soap_tmp_t__gmt;
	struct t__gmtResponse *soap_tmp_t__gmtResponse;
	soap_begin(soap);
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	soap_serialize_t__gmt(soap, &soap_tmp_t__gmt);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_t__gmt(soap, &soap_tmp_t__gmt, "t:gmt", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_url(soap, soap_endpoint, NULL), soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_t__gmt(soap, &soap_tmp_t__gmt, "t:gmt", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!_param_1)
		return soap_closesock(soap);
	soap_default_time(soap, _param_1);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_tmp_t__gmtResponse = soap_get_t__gmtResponse(soap, NULL, "t:gmtResponse", "");
	if (!soap_tmp_t__gmtResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (_param_1 && soap_tmp_t__gmtResponse->_param_1)
		*_param_1 = *soap_tmp_t__gmtResponse->_param_1;
	return soap_closesock(soap);
}
