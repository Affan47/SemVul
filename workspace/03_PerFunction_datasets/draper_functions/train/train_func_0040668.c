getDOMElementValue(const DOMElement* pElem, UINT64 &value)
{
	ASSERT(pElem!=NULL, "Element is NULL");
	UINT8 buf[256];
	UINT32 bufLen = 256;
	if(getDOMElementValue(pElem,buf,&bufLen)!=E_SUCCESS)
	{
		return E_UNKNOWN;
	}
	if(parseU64(buf, value)!=E_SUCCESS)
	{
		return E_UNKNOWN;
	}

	return E_SUCCESS;
}
