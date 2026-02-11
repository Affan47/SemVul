setsd(const FourByteLong iseed1,const FourByteLong iseed2)


{
extern void gsrgs(const FourByteLong getset,FourByteLong *const qvalue);
extern void gscgn(FourByteLong getset,FourByteLong *g);
extern FourByteLong Xig1[],Xig2[];
static FourByteLong g;
static FourByteLong qrgnin;


    gsrgs(0L,&qrgnin);
    if(qrgnin) goto S10;
    stop( " SETSD called before random number generator  initialized -- abort!");
S10:
    gscgn(0L,&g);
    *(Xig1+g-1) = iseed1;
    *(Xig2+g-1) = iseed2;
    initgn(-1L);
}
