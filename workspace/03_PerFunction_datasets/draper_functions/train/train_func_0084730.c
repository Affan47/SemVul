Calc_instantiate(struct soap *soap, int t, const char *type, const char *arrayType, size_t *n)
{	(void)type;
	switch (t)
	{
	case SOAP_TYPE_Calc_ns__addResponse:
		return (void*)soap_instantiate_ns__addResponse(soap, -1, type, arrayType, n);
	case SOAP_TYPE_Calc_ns__add:
		return (void*)soap_instantiate_ns__add(soap, -1, type, arrayType, n);
	case SOAP_TYPE_Calc_ns__subResponse:
		return (void*)soap_instantiate_ns__subResponse(soap, -1, type, arrayType, n);
	case SOAP_TYPE_Calc_ns__sub:
		return (void*)soap_instantiate_ns__sub(soap, -1, type, arrayType, n);
	case SOAP_TYPE_Calc_ns__mulResponse:
		return (void*)soap_instantiate_ns__mulResponse(soap, -1, type, arrayType, n);
	case SOAP_TYPE_Calc_ns__mul:
		return (void*)soap_instantiate_ns__mul(soap, -1, type, arrayType, n);
	case SOAP_TYPE_Calc_ns__divResponse:
		return (void*)soap_instantiate_ns__divResponse(soap, -1, type, arrayType, n);
	case SOAP_TYPE_Calc_ns__div:
		return (void*)soap_instantiate_ns__div(soap, -1, type, arrayType, n);
	case SOAP_TYPE_Calc_ns__powResponse:
		return (void*)soap_instantiate_ns__powResponse(soap, -1, type, arrayType, n);
	case SOAP_TYPE_Calc_ns__pow:
		return (void*)soap_instantiate_ns__pow(soap, -1, type, arrayType, n);
#ifndef WITH_NOGLOBAL
	case SOAP_TYPE_Calc_SOAP_ENV__Header:
		return (void*)soap_instantiate_SOAP_ENV__Header(soap, -1, type, arrayType, n);
#endif
#ifndef WITH_NOGLOBAL
	case SOAP_TYPE_Calc_SOAP_ENV__Code:
		return (void*)soap_instantiate_SOAP_ENV__Code(soap, -1, type, arrayType, n);
#endif
#ifndef WITH_NOGLOBAL
	case SOAP_TYPE_Calc_SOAP_ENV__Detail:
		return (void*)soap_instantiate_SOAP_ENV__Detail(soap, -1, type, arrayType, n);
#endif
#ifndef WITH_NOGLOBAL
	case SOAP_TYPE_Calc_SOAP_ENV__Reason:
		return (void*)soap_instantiate_SOAP_ENV__Reason(soap, -1, type, arrayType, n);
#endif
#ifndef WITH_NOGLOBAL
	case SOAP_TYPE_Calc_SOAP_ENV__Fault:
		return (void*)soap_instantiate_SOAP_ENV__Fault(soap, -1, type, arrayType, n);
#endif
	}
	return NULL;
}
