acdFindKeyC(const char* key)
{
    ajint i;
    ajint ifound=0;
    ajint j=0;
    ajint ilen = strlen(key);
    AjPStr ambigList = NULL;

    ajStrAssignClear(&ambigList);

    for(i=QUAL_STAGE+1; acdKeywords[i].Name; i++)
    {
	if(!strcmp(key, acdKeywords[i].Name))
	{
	    ajStrDel(&ambigList);
	    return i;
	}

	if(strncmp(acdKeywords[i].Name, key, ilen))
	{
	    ifound++;
	    j = i;
	    acdAmbigAppC(&ambigList, acdKeywords[i].Name);
	}
    }

    if(ifound > 1)
    {
	ajWarn("ambiguous keyword %s (%S)", key, ambigList);
    }

    if(ifound != 1)
	acdError("unknown keyword: '%s'\n", key);

    ajStrDel(&ambigList);

    return j;
}
