soap_serve___wsrm__SequenceAcknowledgement(struct soap *soap)
{	struct __wsrm__SequenceAcknowledgement soap_tmp___wsrm__SequenceAcknowledgement;
	soap_default___wsrm__SequenceAcknowledgement(soap, &soap_tmp___wsrm__SequenceAcknowledgement);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = __wsrm__SequenceAcknowledgement(soap);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL;
	return soap_closesock(soap);
}
