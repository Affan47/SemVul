getDOMElementAttribute(const DOMNode * const elem,const char* attrName,bool& value)
{
	UINT8 val[50];
	UINT32 len=50;
	if(getDOMElementAttribute(elem,attrName,val,&len) != E_SUCCESS)
	{
		return E_UNKNOWN;
	}
	SINT32 ret = E_UNSPECIFIED;
	if(strncasecmp((char*)val, STR_VALUE_TRUE, strlen(STR_VALUE_TRUE)) == 0)
	{
		value = true;
		ret = E_SUCCESS;
	}
	else if(strncasecmp((char*)val, STR_VALUE_FALSE, strlen(STR_VALUE_FALSE)) == 0)
	{
		value = false;
		ret = E_SUCCESS;
	}
	return ret;
}
