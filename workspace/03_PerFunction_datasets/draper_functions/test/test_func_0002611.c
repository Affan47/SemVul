arrChararrResize(AjPChar *thys, ajuint size)
{
    AjPChar p = NULL;
    ajuint    s;
    ajuint    clen;
    ajuint    limit;


    if(!thys || !*thys)
	ajErr("Illegal attempt to resize character array");

    clen = ajRound((*thys)->Len-1,RESERVED_SIZE);
    s = ajRound(size+1,RESERVED_SIZE);

    if(s <= clen)
	return ajFalse;


    p = *thys;

    *thys = ajChararrNewRes(s);

    if(size < p->Len)
	limit = size+1;
    else
	limit = p->Len;

    memmove((*thys)->Ptr,p->Ptr,limit*sizeof(char));

    (*thys)->Len = size+1;


    ajChararrDel(&p);

    arrResize++;

    return ajTrue;
}
