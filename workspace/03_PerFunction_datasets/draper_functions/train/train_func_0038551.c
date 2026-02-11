Quote_fdelete(struct soap_clist *p)
{	switch (p->type)
	{
	case SOAP_TYPE_Quote_ns__getQuoteResponse:
		if (p->size < 0)
			SOAP_DELETE((struct ns__getQuoteResponse*)p->ptr);
		else
			SOAP_DELETE_ARRAY((struct ns__getQuoteResponse*)p->ptr);
		break;
	case SOAP_TYPE_Quote_ns__getQuote:
		if (p->size < 0)
			SOAP_DELETE((struct ns__getQuote*)p->ptr);
		else
			SOAP_DELETE_ARRAY((struct ns__getQuote*)p->ptr);
		break;
#ifndef WITH_NOGLOBAL
	case SOAP_TYPE_Quote_SOAP_ENV__Header:
		if (p->size < 0)
			SOAP_DELETE((struct SOAP_ENV__Header*)p->ptr);
		else
			SOAP_DELETE_ARRAY((struct SOAP_ENV__Header*)p->ptr);
		break;
#endif
#ifndef WITH_NOGLOBAL
	case SOAP_TYPE_Quote_SOAP_ENV__Code:
		if (p->size < 0)
			SOAP_DELETE((struct SOAP_ENV__Code*)p->ptr);
		else
			SOAP_DELETE_ARRAY((struct SOAP_ENV__Code*)p->ptr);
		break;
#endif
#ifndef WITH_NOGLOBAL
	case SOAP_TYPE_Quote_SOAP_ENV__Detail:
		if (p->size < 0)
			SOAP_DELETE((struct SOAP_ENV__Detail*)p->ptr);
		else
			SOAP_DELETE_ARRAY((struct SOAP_ENV__Detail*)p->ptr);
		break;
#endif
#ifndef WITH_NOGLOBAL
	case SOAP_TYPE_Quote_SOAP_ENV__Reason:
		if (p->size < 0)
			SOAP_DELETE((struct SOAP_ENV__Reason*)p->ptr);
		else
			SOAP_DELETE_ARRAY((struct SOAP_ENV__Reason*)p->ptr);
		break;
#endif
#ifndef WITH_NOGLOBAL
	case SOAP_TYPE_Quote_SOAP_ENV__Fault:
		if (p->size < 0)
			SOAP_DELETE((struct SOAP_ENV__Fault*)p->ptr);
		else
			SOAP_DELETE_ARRAY((struct SOAP_ENV__Fault*)p->ptr);
		break;
#endif
	default:	return SOAP_ERR;
	}
	return SOAP_OK;
}
