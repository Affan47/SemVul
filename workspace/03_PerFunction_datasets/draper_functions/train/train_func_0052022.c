Gprint(argn,nl)
int argn;
int nl;
{
    truc *ptr;
    truc strom;
    truc obj;
    int changecols = 0;
    int savemode, flg;
    int i;

    strom = tstdout;
    if(argn > 0) {
        ptr = argStkPtr - argn + 1;
        flg = *FLAGPTR(ptr);
        if(flg == fTUPLE) {
            obj = *ptr;
            if(*VECLENPTR(ptr) >= 2) {
                ptr = VECTOR(obj);
                flg = *FLAGPTR(ptr);
                changecols = 1;
            }
        }
        if(flg == fSTREAM) {
            if(!isoutfile(ptr,aTEXT)) {
                error(writesym,err_tout,voidsym);
                return(-1);
            }
            else {
                argn--;
                strom = *ptr;
            }
            if(changecols) {
                PrintCols = setcols(strom,ptr+1);
            }
        }
    }
    savemode = quotemode;
    quotemode = 0;
    for(i=-argn+1; i<=0; i++) {
        tprint(strom,argStkPtr[i]);
    }
    if(nl)
        fnewline(strom);
    quotemode = savemode;
    PrintCols = MaxCols-1;
    return(argn);
}
