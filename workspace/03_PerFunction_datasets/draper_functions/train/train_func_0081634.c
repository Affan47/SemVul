acdParseAlpha(AjPList listwords, AjPStr* pword)
{
    if(acdWordNextLower(listwords, pword))
	if(ajStrIsAlpha(*pword))
	    return;


    acdError("Bad or missing %s alphabetic name '%S'",
	     acdKeywords[acdCurrentStage].Name, *pword);

    return;
}
