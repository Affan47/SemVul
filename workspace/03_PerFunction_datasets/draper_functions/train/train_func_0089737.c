ajStrTrimC(AjPStr* Pstr, const char* txt)
{
    AjPStr thys;
    const char* cp;
    size_t i;

    if(!*Pstr)
        *Pstr = ajStrNewResLenC("", 1, 0);
    else if((*Pstr)->Use > 1)
        ajStrGetuniqueStr(Pstr);

    thys = *Pstr;

    cp = thys->Ptr;
    i = strspn(cp, txt);

    if(i)
    {
	thys->Len -= i;

	if(thys->Len)
	    memmove(thys->Ptr, &thys->Ptr[i], thys->Len);
	else
	    *thys->Ptr = '\0';
    }

    if(i)
	thys->Ptr[thys->Len] = '\0';

    if(!thys->Len)
	return ajFalse;


    cp = &thys->Ptr[thys->Len-1];
    i = 0;

    while(thys->Len && strchr(txt, *cp))
    {
	i++;
	thys->Len--;

	if(thys->Len)
	    cp--;
    }

    if(i)
	thys->Ptr[thys->Len] = '\0';

    return ajTrue;
}
