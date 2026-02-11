UT_UTF8String_removeProperty(UT_UTF8String & sPropertyString, const UT_UTF8String & sProp)
{


	size_t offset = 0;
	UT_UTF8String sWork ( sProp );
	sWork += ":";
	const char * szWork = sWork.utf8_str();
	const char * szProps = sPropertyString.utf8_str();
	const char * szLoc = strstr(szProps,szWork);

	if(!szLoc)
	{

		return ;
	}


	if (szLoc != szProps)
	{


		UT_UTF8String sWorkCheck("; ");
		sWorkCheck += sWork;
		const char * szLocCheck = strstr(szProps,sWorkCheck.utf8_str());
		if (!szLocCheck)
		{

			return;
		}
		szLoc = szLocCheck;
		offset = 1;
	}

	UT_sint32 locLeft = static_cast<UT_sint32>(reinterpret_cast<size_t>(szLoc) - reinterpret_cast<size_t>(szProps));
	UT_UTF8String sLeft;
	if(locLeft == 0)
	{
		sLeft.clear();
	}
	else
	{
		sLeft = sPropertyString.substr(0,locLeft);
	}

	UT_UTF8String sNew;
	if(locLeft > 0)
	{
		sNew = sLeft;
	}
	else
	{
		sNew.clear();
	}


	const char * szDelim = strchr(szLoc + offset,';');
	if(szDelim == NULL)
	{

		sPropertyString = sNew;
	}
	else
	{

		while(*szDelim == ';' || *szDelim == ' ')
		{
			szDelim++;
		}
		UT_UTF8String sRight = szDelim;
		if(sNew.size() > 0)
		{
			sNew += "; ";
		}
		sNew += sRight;
		sPropertyString = sNew;
	}
}
