setAttribute(const XMLString& name, const XMLString& value)
{
	Attr* pAttr = getAttributeNode(name);
	if (pAttr)
	{
		pAttr->setValue(value);
	}
	else
	{
		pAttr = ownerDocument()->createAttribute(name);
		pAttr->setValue(value);
		setAttributeNode(pAttr);
		pAttr->release();
	}
}
