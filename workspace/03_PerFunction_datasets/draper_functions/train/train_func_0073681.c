Fmemavail(argn)
int argn;
{
    long s[4];
    unsigned f;
    int verbose;

    verbose = (argn == 0 || *argStkPtr != zero);

    memstatistics(s);
    if(verbose) {
        gcstatistics();
        displaymem(s);
    }
    f = s[2] >> 10;
    return(mkfixnum(f));
}
