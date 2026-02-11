ajSysFuncStrtok(const char *srcstr, const char *delimstr)
{
    ajint len;

    if(srcstr)
    {
	if(!sysTokRets)
	{
	    sysTokSou  = ajStrNew();
	    sysTokRets = ajStrNew();
	}
	ajStrAssignC(&sysTokSou,srcstr);
	sysTokp = ajStrGetPtr(sysTokSou);
    }

    if(!*sysTokp)
	return NULL;

    len = strspn(sysTokp,delimstr);
    sysTokp += len;
    if(!*sysTokp)
	return NULL;

    len = strcspn(sysTokp,delimstr);
    ajStrAssignSubC(&sysTokRets,sysTokp,0,len-1);
    sysTokp += len;

    return ajStrGetuniquePtr(&sysTokRets);
}
