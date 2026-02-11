ajStrAssignResC(AjPStr* Pstr, size_t size, const char* txt)
{
    AjBool ret = ajFalse;
    AjPStr thys;
    size_t ilen;
    size_t isize;

    if (txt)
	ilen = strlen(txt);
    else
	ilen = 0;

    isize = size;

    if(ilen >= isize)
	isize = ilen + 1;

    ret = ajStrSetResRound(Pstr, isize);
    thys = *Pstr;

    thys->Len = ilen;

    if(ilen)
	memmove(thys->Ptr, txt, ilen);

    thys->Ptr[ilen] = '\0';

    return ret;
}
