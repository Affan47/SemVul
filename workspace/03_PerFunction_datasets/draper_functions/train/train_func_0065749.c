ignuin(const FourByteLong low, const FourByteLong high)


{
#define maxnum 2147483561L
static FourByteLong ignuin,ign,maxnow,range,ranp1;

    if(!(low > high)) goto S10;
    stop("ERROR low > high in ignuin");

S10:
    range = high-low;
    if(!(range > maxnum)) goto S20;
    stop("ERROR high - low too large in ignuin");

S20:
    if(!(low == high)) goto S30;
    ignuin = low;
    return ignuin;

S30:


    ranp1 = range+1;
    maxnow = maxnum/ranp1*ranp1;
S40:
    ign = ignlgi()-1;
    if(!(ign <= maxnow)) goto S50;
    ignuin = low+ign%ranp1;
    return ignuin;
S50:
    goto S40;
#undef maxnum
#undef err1
#undef err2
}
