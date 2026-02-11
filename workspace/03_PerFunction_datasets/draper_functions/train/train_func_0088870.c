setAttribute(const c8* attributeName, video::SColor value)
{
	IAttribute* att = getAttributeP(attributeName);
	if (att)
		att->setColor(value);
	else
		Attributes.push_back(new CColorAttribute(attributeName, value));
}
