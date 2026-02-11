getAttributeAsStringW(const c8* attributeName)
{
	core::stringw str;

	IAttribute* att = getAttributeP(attributeName);
	if (att)
		str = att->getStringW();

	return str;
}
