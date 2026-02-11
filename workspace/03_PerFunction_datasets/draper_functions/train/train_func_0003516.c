iom_getattrvalueUTF8(IOM_OBJECT object,IOM_TAG attrName)
{
	static char *value=0;
	if(value){
		XMLString::release(&value);
	}
	int nameId=ParserHandler::getTagId(attrName);
	if(!nameId) return 0;
	const XMLCh *ret=object->getAttrValue(nameId);
	if(!ret)return 0;
	value=iom_toUTF8(ret);
	return value;
}
