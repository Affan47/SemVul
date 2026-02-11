arrFloat3dResize(AjPFloat3d *thys, ajuint size)
{
    AjPFloat3d nthys;
    AjPFloat3d p = NULL;
    ajuint    s;
    ajuint    clen;
    ajuint    limit;
    ajuint    i;


    if(!thys || !*thys)
	ajErr("Illegal attempt to resize float array");

    clen = ajRound((*thys)->Len-1,RESERVED_SIZE);
    s = ajRound(size+1,RESERVED_SIZE);

    if(s <= clen)
	return ajFalse;


    p = *thys;

    AJNEW0(nthys);
    nthys->Ptr = AJALLOC0(s*sizeof(AjPFloat2d));
    nthys->Res = s;

    if(size < p->Len)
	limit = size+1;
    else
	limit = p->Len;

    memmove(nthys->Ptr,p->Ptr,limit*sizeof(AjPFloat2d));

    i = nthys->Len = size+1;


    for(;i<p->Res;++i)
	if(p->Ptr[i])
	    ajFloat2dDel(&p->Ptr[i]);

    AJFREE(p->Ptr);
    AJFREE(p);

    *thys = nthys;

    arr3dResize++;

    return ajTrue;
}
