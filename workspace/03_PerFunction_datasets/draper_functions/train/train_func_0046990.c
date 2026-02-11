ignnbn(const FourByteLong n, ConstReal p)


{
static FourByteLong ignnbn;
static Real y,a,r;


    if(n < 0) stop("N < 0 in IGNNBN");
    if(p <= 0.0F) stop("P <= 0 in IGNNBN");
    if(p >= 1.0F) stop("P >= 1 in IGNNBN");


    r = (Real)n;
    a = p/(1.0F-p);
    y = gengam(a,r);


    ignnbn = ignpoi(y);
    return ignnbn;
}
