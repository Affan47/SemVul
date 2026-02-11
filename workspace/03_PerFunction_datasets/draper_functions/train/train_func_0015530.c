setSpacing(bool vl)
{
	if (vl != arrangement.spacing)
	{
		arrangement.spacing = vl;
		performArrange();
	}
}
