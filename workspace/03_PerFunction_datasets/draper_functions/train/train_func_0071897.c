serve___ns5__dtx(mashupService *soap)
{	struct __ns5__dtx soap_tmp___ns5__dtx;
	_ns3__commingtotown ns3__commingtotown;
	ns3__commingtotown.soap_default(soap);
	soap_default___ns5__dtx(soap, &soap_tmp___ns5__dtx);
	if (!soap_get___ns5__dtx(soap, &soap_tmp___ns5__dtx, "-ns5:dtx", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = soap->dtx(soap_tmp___ns5__dtx.ns3__daystoxmas, &ns3__commingtotown);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL;
	soap_serializeheader(soap);
	ns3__commingtotown.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns3__commingtotown.soap_put(soap, "ns3:commingtotown", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns3__commingtotown.soap_put(soap, "ns3:commingtotown", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}
