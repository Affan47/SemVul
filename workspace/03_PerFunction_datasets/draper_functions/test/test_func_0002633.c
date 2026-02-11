ajStrKeepSetAlphaRest(AjPStr* Pstr, AjPStr* Prest)
{
    AjPStr thys = NULL;
    char *p = NULL;
    char *q = NULL;

    ajStrAssignClear(Prest);

    if(!*Pstr)
        *Pstr = ajStrNewResLenC("", 1, 0);
    else if((*Pstr)->Use > 1)
        ajStrGetuniqueStr(Pstr);

    thys = *Pstr;

    p = thys->Ptr;
    q = thys->Ptr;

    while(*p)
    {
	if(isalpha((ajint)*p))
	    *q++=*p;
	else if(!isspace((ajint)*p))
	    ajStrAppendK(Prest, *p);

	p++;
    }

    *q='\0';
    thys->Len = q - thys->Ptr;

    if(!thys->Len)
        return ajFalse;

    return ajTrue;
}
