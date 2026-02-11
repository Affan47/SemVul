Fversion(argn)
int argn;
{
    if(argn == 0 || *argStkPtr != zero) {
        s2form(OutBuf,"ARIBAS Version ~A (~A)",
            strcast(Version),strcast(architec));
        fprintline(tstdout,OutBuf);
    }
    return(mkfixnum(version_no));
}
