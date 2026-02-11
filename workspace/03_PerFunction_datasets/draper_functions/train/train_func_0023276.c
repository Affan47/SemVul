soap_in___wsrm__TerminateSequence(struct soap *soap, const char *tag, struct __wsrm__TerminateSequence *a, const char *type)
{
	size_t soap_flag_wsrm__TerminateSequence = 1;
	short soap_flag;
	a = (struct __wsrm__TerminateSequence *)soap_id_enter(soap, "", a, SOAP_TYPE___wsrm__TerminateSequence, sizeof(struct __wsrm__TerminateSequence), 0, NULL, NULL, NULL);
	if (!a)
		return NULL;
	soap_default___wsrm__TerminateSequence(soap, a);
		for (soap_flag = 0;; soap_flag = 1)
		{	soap->error = SOAP_TAG_MISMATCH;
			if (soap_flag_wsrm__TerminateSequence && soap->error == SOAP_TAG_MISMATCH)
				if (soap_in_PointerTowsrm__TerminateSequenceType(soap, "wsrm:TerminateSequence", &a->wsrm__TerminateSequence, "wsrm:TerminateSequenceType"))
				{	soap_flag_wsrm__TerminateSequence--;
					continue;
				}
			if (soap->error == SOAP_TAG_MISMATCH)
				if (soap_flag)
				{	soap->error = SOAP_OK;
					break;
				}
			if (soap_flag && soap->error == SOAP_NO_TAG)
				break;
			if (soap->error)
				return NULL;
		}
	return a;
}
