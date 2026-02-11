ptrtypeval(typ)
truc typ;
{
    struct symbol *sptr;
    truc *ptr;
    truc obj;
    int flg;
    int depth = 0;

  nochmal:
    if(++depth > 64) {
        error(typesym,err_rec,mkfixnum(depth));
        goto errexit;
    }
    sptr = symptr(typ);
    if(*FLAGPTR(sptr) != sTYPEDEF)
        goto errexit;
    typ = sptr->bind.t;
    flg = Tflag(typ);
    if(flg == fSYMBOL)
        goto nochmal;
    else if(flg == fBUILTIN1) {
        ptr = Taddress(typ);
        if(ptr[0] != mkrecsym)
            goto errexit;
        obj = ptr[1];
        flg = Tflag(obj);
        if(flg == fSYMBOL) {
            typ = obj;
            goto nochmal;
        }
        else if(flg == fTUPLE)
            return(obj);
    }
  errexit:
    return(parserrsym);
}
