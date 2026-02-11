Fgetenv()
{
    char *estr;

    if(*FLAGPTR(argStkPtr) != fSTRING) {
        error(getenvsym,err_str,*argStkPtr);
        return(brkerr());
    }
    estr = getenv(STRINGPTR(argStkPtr));
    if(estr == NULL) {
        return(nullstring);
    }
    else {
        return(mkstr(estr));
    }
}
