genmul(const FourByteLong n, const Real *const p, const FourByteLong ncat,  FourByteLong *const ix)


{
static Real prob,ptot,sum;
static FourByteLong i,icat,ntot;
    if(n < 0) stop("N < 0 in GENMUL");
    if(ncat <= 1) stop("NCAT <= 1 in GENMUL");
    ptot = 0.0F;
    for (i=0; i<ncat-1; i++) {
        if(*(p+i) < 0.0F) stop("Some P(i) < 0 in GENMUL");
        if(*(p+i) > 1.0F) stop("Some P(i) > 1 in GENMUL");
        ptot += *(p+i);
    }
    if(ptot > 0.99999F) stop("Sum of P(i) > 1 in GENMUL");


    ntot = n;
    sum = 1.0F;
    for (i=0; i<ncat; i++) ix[i] = 0;


    for (icat=0; icat<ncat-1; icat++) {
        prob = *(p+icat)/sum;
        *(ix+icat) = ignbin(ntot,prob);
        ntot -= *(ix+icat);
	if(ntot <= 0) return;
        sum -= *(p+icat);
    }
    *(ix+ncat-1) = ntot;


    return;
}
