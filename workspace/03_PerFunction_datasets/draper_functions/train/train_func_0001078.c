soap_fdelete(struct soap_clist *p)
{	switch (p->type)
	{
	case SOAP_TYPE_vector:
		if (p->size < 0)
			SOAP_DELETE((vector*)p->ptr);
		else
			SOAP_DELETE_ARRAY((vector*)p->ptr);
		break;
	case SOAP_TYPE_matrix:
		if (p->size < 0)
			SOAP_DELETE((matrix*)p->ptr);
		else
			SOAP_DELETE_ARRAY((matrix*)p->ptr);
		break;
	case SOAP_TYPE_ns1__magicResponse:
		if (p->size < 0)
			SOAP_DELETE((struct ns1__magicResponse*)p->ptr);
		else
			SOAP_DELETE_ARRAY((struct ns1__magicResponse*)p->ptr);
		break;
	case SOAP_TYPE_ns1__magic:
		if (p->size < 0)
			SOAP_DELETE((struct ns1__magic*)p->ptr);
		else
			SOAP_DELETE_ARRAY((struct ns1__magic*)p->ptr);
		break;
#ifndef WITH_NOGLOBAL
	case SOAP_TYPE_SOAP_ENV__Header:
		if (p->size < 0)
			SOAP_DELETE((struct SOAP_ENV__Header*)p->ptr);
		else
			SOAP_DELETE_ARRAY((struct SOAP_ENV__Header*)p->ptr);
		break;
#endif
#ifndef WITH_NOGLOBAL
	case SOAP_TYPE_SOAP_ENV__Code:
		if (p->size < 0)
			SOAP_DELETE((struct SOAP_ENV__Code*)p->ptr);
		else
			SOAP_DELETE_ARRAY((struct SOAP_ENV__Code*)p->ptr);
		break;
#endif
#ifndef WITH_NOGLOBAL
	case SOAP_TYPE_SOAP_ENV__Detail:
		if (p->size < 0)
			SOAP_DELETE((struct SOAP_ENV__Detail*)p->ptr);
		else
			SOAP_DELETE_ARRAY((struct SOAP_ENV__Detail*)p->ptr);
		break;
#endif
#ifndef WITH_NOGLOBAL
	case SOAP_TYPE_SOAP_ENV__Reason:
		if (p->size < 0)
			SOAP_DELETE((struct SOAP_ENV__Reason*)p->ptr);
		else
			SOAP_DELETE_ARRAY((struct SOAP_ENV__Reason*)p->ptr);
		break;
#endif
#ifndef WITH_NOGLOBAL
	case SOAP_TYPE_SOAP_ENV__Fault:
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
