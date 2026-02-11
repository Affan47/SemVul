gennch(float df,float xnonc)


{
static float gennch;

    if(!(df < 1.0 || xnonc < 0.0)) goto S10;
    fputs("DF < 1 or XNONC < 0 in GENNCH - ABORT\n",stderr);
    fprintf(stderr,"Value of DF: %16.6E Value of XNONC: %16.6E\n",df,xnonc);
    exit(1);

S10:
    if(df >= 1.000001) goto S20;


    gennch = pow(snorm()+sqrt(xnonc),2.0);
    goto S30;
S20:


    gennch = 2.0*sgamma((df-1.0)/2.0)+pow(snorm()+sqrt(xnonc),2.0);
S30:
    return gennch;
}
