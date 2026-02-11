env_instantiate(struct soap *soap, int t, const char *type, const char *arrayType, size_t *n)
{	(void)type;
	switch (t)
	{
	case SOAP_TYPE_h__authentication:
		return (void*)soap_instantiate_h__authentication(soap, -1, type, arrayType, n);
#ifndef WITH_NOGLOBAL
	case SOAP_TYPE_SOAP_ENV__Header:
		return (void*)soap_instantiate_SOAP_ENV__Header(soap, -1, type, arrayType, n);
#endif
#ifndef WITH_NOGLOBAL
	case SOAP_TYPE_SOAP_ENV__Code:
		return (void*)soap_instantiate_SOAP_ENV__Code(soap, -1, type, arrayType, n);
#endif
#ifndef WITH_NOGLOBAL
	case SOAP_TYPE_SOAP_ENV__Detail:
		return (void*)soap_instantiate_SOAP_ENV__Detail(soap, -1, type, arrayType, n);
#endif
#ifndef WITH_NOGLOBAL
	case SOAP_TYPE_SOAP_ENV__Reason:
		return (void*)soap_instantiate_SOAP_ENV__Reason(soap, -1, type, arrayType, n);
#endif
#ifndef WITH_NOGLOBAL
	case SOAP_TYPE_SOAP_ENV__Fault:
		return (void*)soap_instantiate_SOAP_ENV__Fault(soap, -1, type, arrayType, n);
#endif
	}
	return NULL;
}
