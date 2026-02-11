ajBtreeKeywildNew(AjPBtcache cache, const AjPStr wild)
{
    AjPBtKeywild thys = NULL;

    char *p;
    char *cp;

    AJNEW0(thys);

    thys->keyword = ajStrNewS(wild);
    ajStrFmtQuery(&thys->keyword);
    if(MAJSTRGETLEN(thys->keyword) > cache->keylimit)
        ajStrTruncateLen(&thys->keyword, cache->keylimit);

    cp = MAJSTRGETPTR(thys->keyword);
    p = strpbrk(cp,"*?");

    if(p)
    {
	if(p-cp)
	    ajStrAssignSubS(&thys->prefix,thys->keyword,0,p-cp-1);
	else
            ajStrAssignC(&thys->prefix, "");
    }
    else
	ajStrAssignS(&thys->prefix,thys->keyword);

    thys->list   = ajListNew();
    thys->idlist = ajListNew();

    thys->first = ajTrue;

    return thys;
}
