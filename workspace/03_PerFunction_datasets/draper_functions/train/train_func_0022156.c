addvecs(sym,ptr)
truc sym;
truc *ptr;
{
    truc tmp;
    int len1, len2, flg1, flg;

    flg1 = chknumvec(sym,ptr);
    if(flg1 == aERROR)
        return brkerr();
    flg = chknumvec(sym,ptr+1);
    if(flg == aERROR) {
        return brkerr();
    }
    if(flg < flg1)
        flg = flg1;

    if(sym == minussym) {
        ptr[1] = mkcopy(ptr+1);
        ptr[1] = negatevec(ptr+1);
    }
    len1 = *VECLENPTR(ptr);
    len2 = *VECLENPTR(ptr+1);
    if(len2 < len1) {
        tmp = mkcopy(ptr);
        ptr[0] = ptr[1];
        ptr[1] = tmp;
    }
    else if(sym == plussym) {
        ptr[1] = mkcopy(ptr+1);
    }
    if(flg <= fBIGNUM) {
        return addintvecs(ptr,ptr+1);
    }
    else {
        curFltPrec = deffltprec();
        return addfltvecs(ptr,ptr+1);
    }
}
