Fsubarr()
{
    truc *ptr, *ptr1;
    truc obj;
    char *cptr, *cptr1;
    long len, len0, n0, n1;
    int flg;

    flg = *FLAGPTR(argStkPtr-1);
    if(flg < fVECTLIKE0 && flg > fVECTLIKE1) {
        error(subarrsym,err_arr,argStkPtr[-1]);
        return(brkerr());
    }
    len = *VECLENPTR(argStkPtr-1);

    if(indrange(argStkPtr,len,&n0,&n1) == aERROR) {
        return(brkerr());
    }
    len0 = n1 - n0 + 1;
    if(flg == fVECTOR) {
        obj = mkvect0((unsigned)len0);
        ptr1 = VECTORPTR(argStkPtr-1) + n0;
        ptr = VECTOR(obj);
        while(--len0 >= 0)
            *ptr++ = *ptr1++;
        return(obj);
    }
    if(flg == fSTRING)
        obj = mkstr0((unsigned)len0);
    else if(flg == fBYTESTRING)
        obj = mkbstr0((unsigned)len0);
    else
        return(brkerr());


    cptr1 = STRINGPTR(argStkPtr-1) + n0;
    cptr = STRING(obj);
    while(--len0 >= 0)
        *cptr++ = *cptr1++;
    *cptr = 0;
    return(obj);
}
