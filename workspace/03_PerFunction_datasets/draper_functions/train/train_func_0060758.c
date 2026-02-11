Flog()
{
    numdata acc;
    int prec;
    int ret;

    prec = Gget1flt(logsym,&acc);
    if(prec == aERROR)
        return(brkerr());
    ret = lognum(prec,&acc,AriScratch);
    if(ret == aERROR) {
        error(logsym,err_pnum,*argStkPtr);
        return(brkerr());
    }
    return(mkfloat(curfltprec,&acc));
}
