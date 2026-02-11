acdWordNextLower(AjPList listwords, AjPStr* pword)
{
    if(acdWordNext(listwords, pword))
    {
	if(!ajStrIsLower(*pword))
	{
	    acdWarn("Automatically converting '%S' to lower case", *pword);
	    ajStrFmtLower(pword);
	}
	return ajTrue;
    }

    return ajFalse;
}
