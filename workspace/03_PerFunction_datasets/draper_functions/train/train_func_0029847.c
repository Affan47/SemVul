ajCharCmpCaseLen(const char* txt, const char* txt2, size_t len)
{
    const char* cp;
    const char* cq;
    size_t i;

    for(cp=txt,cq=txt2,i=0;*cp && *cq && i<len;++i,++cp,++cq)
	if(toupper((int) *cp) != toupper((int) *cq))
	{
	    if(toupper((int) *cp) > toupper((int) *cq))
		return 1;
	    else
		return -1;
	}

    if(i==len)
	return 0;

    if(*cp)
	return 1;

    return -1;
}
