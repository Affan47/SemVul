gennch(ConstReal df, ConstReal xnonc)


{
static Real gennch;

    if(!(df <= 1.0 || xnonc < 0.0)) goto S10;
    fputs("DF <= 1 or XNONC < 0 in GENNCH - ABORT",stderr);
    fprintf(stderr,"Value of DF: %16.6E Value of XNONC%16.6E\n",df,xnonc);
    stop("ERROR in gennch");
S10:
    gennch = genchi(df-1.0)+pow(gennor(sqrt(xnonc),1.0),2.0);
    return gennch;
}
