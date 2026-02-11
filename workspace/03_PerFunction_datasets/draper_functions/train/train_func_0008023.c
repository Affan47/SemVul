getDOMElementValue(const DOMElement* const pElem,double* value)
{
	ASSERT(value!=NULL,"Value is null");
	ASSERT(pElem!=NULL,"Element is NULL");
	UINT8 buff[255];
	UINT32 buffLen=255;
	if(getDOMElementValue(pElem,buff,&buffLen)!=E_SUCCESS)
		return E_UNKNOWN;
	*value=atof((char*)buff);

	return E_SUCCESS;
}
