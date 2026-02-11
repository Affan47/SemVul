soap_call_ns__getData(struct soap *soap, const char *soap_endpoint, const char *soap_action, arrayOfName *names, arrayOfData *data)
{	struct ns__getData soap_tmp_ns__getData;
	struct ns__getDataResponse *soap_tmp_ns__getDataResponse;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://websrv.cs.fsu.edu/~engelen/dimesrv.cgi";
	soap_begin(soap);
	soap->encodingStyle = "";
	soap_tmp_ns__getData.names = names;
	soap_serializeheader(soap);
	soap_serialize_ns__getData(soap, &soap_tmp_ns__getData);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__getData(soap, &soap_tmp_ns__getData, "ns:getData", NULL)
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
	 || soap_put_ns__getData(soap, &soap_tmp_ns__getData, "ns:getData", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!data)
		return soap_closesock(soap);
	data->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	if (soap_recv_fault(soap, 1))
		return soap->error;
	soap_tmp_ns__getDataResponse = soap_get_ns__getDataResponse(soap, NULL, "", "");
	if (!soap_tmp_ns__getDataResponse || soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (data && soap_tmp_ns__getDataResponse->data)
		*data = *soap_tmp_ns__getDataResponse->data;
	return soap_closesock(soap);
}
