vsymaux(argptr,depth)
truc *argptr;
unsigned depth;
{
    unsigned u;
    truc *ptr;
    truc sym, obj;

    switch(*FLAGPTR(argptr)) {
    case fSYMBOL:
        return(*argptr);
    case fLSYMBOL:
        u = depth + *WORD2PTR(argptr);
        return(mklocsym(fLRSYMBOL,u));
    case fRSYMBOL:
        return(*LSYMBOLPTR(argptr));
    case fBUILTIN2:
    case fSPECIAL2:
        ptr = TAddress(argptr);
        sym = *ptr;
        ARGpush(ptr[1]);
        ARGpush(ptr[2]);
        if(sym == arr_sym || sym == subarrsym) {
            argStkPtr[-1] = vsymaux(argStkPtr-1,depth);
            argStkPtr[0] = eval(argStkPtr);
        }
        else if(sym == rec_sym) {
            argStkPtr[-1] = vsymaux(argStkPtr-1,depth);
        }
        else {
            ARGnpop(2);
            break;
        }
        obj = mkbnode(sym);
        ARGnpop(2);
        return(obj);
    }
    return(brkerr());
}
