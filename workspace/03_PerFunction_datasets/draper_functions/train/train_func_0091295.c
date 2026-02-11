chktimesargs(argptr)
truc *argptr;
{
    int flg, flg1;
    truc ele;

    flg = *FLAGPTR(argptr);
    flg1 = *FLAGPTR(argptr+1);

    if(flg < fFIXNUM) {
        if(flg == fVECTOR) {
            if(flg1 >= fFIXNUM || flg1 == fGF2NINT) {
                ele = *argptr;
                *argptr = argptr[1];
                *(argptr+1) = ele;
                return (flg1 | (flg << 8));
            }
            else
                return error(timessym,err_num,argptr[1]);
        }
        else if(flg == fGF2NINT) {
            if(flg1 == flg)
                return flg;
            else if(flg1 == fVECTOR)
                return (flg | (flg1 << 8));
        }
        return error(timessym,err_num,*argptr);
    }

    if(flg1 >= fFIXNUM) {
        return (flg1 >= flg ? flg1 : flg);
    }
    else if(flg1 == fVECTOR)
        return (flg | (flg1 << 8));
    else
        return error(timessym,err_num,argptr[1]);
}
