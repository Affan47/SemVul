pingCmd(const char* pagerID)
{


    fxStr provider;
    fxStr PIN;
    fxStr emsg;
    if (mapPagerID(pagerID, provider, PIN, emsg))
	reply(821, "Valid pager ID, no location information available.");
    else
	reply(550, "%s.", (const char*) emsg);
}
