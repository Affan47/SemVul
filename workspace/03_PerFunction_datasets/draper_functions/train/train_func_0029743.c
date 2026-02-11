OKtoCache(ProgramVariable *pv, gfunc *gf)
{
    if (pv->excache == CACHE_OFF)
        return(FALSE);
    if (gf->excache == CACHE_OFF && !pv->cacheattr)
        return(FALSE);
    return(TRUE);
}
