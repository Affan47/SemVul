isHeading(const PD_Style * pStyle, UT_sint32 iDepth) const
{
	if(pStyle == NULL)
	{
		return false;
	}
	if(strstr(pStyle->getName(),"Heading") != 0)
	{
		return true;
	}
	PD_Style * pUpStyle = pStyle->getBasedOn();
	if(pUpStyle != NULL && iDepth > 0)
	{
		return isHeading(pUpStyle,iDepth-1);
	}
	return false;
}
