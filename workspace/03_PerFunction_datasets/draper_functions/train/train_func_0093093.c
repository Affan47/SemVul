ignlgi(void)


{
#define numg 32L
extern void gsrgs(long getset,long *qvalue);
extern void gssst(long getset,long *qset);
extern void gscgn(long getset,long *g);
extern void inrgcm(void);
extern long Xm1,Xm2,Xa1,Xa2,Xcg1[],Xcg2[];
extern long Xqanti[];
static long ignlgi,curntg,k,s1,s2,z;
static long qqssd,qrgnin;


    gsrgs(0L,&qrgnin);
    if(!qrgnin) inrgcm();
    gssst(0,&qqssd);
    if(!qqssd) setall(1234567890L,123456789L);


    gscgn(0L,&curntg);
    s1 = *(Xcg1+curntg-1);
    s2 = *(Xcg2+curntg-1);
    k = s1/53668L;
    s1 = Xa1*(s1-k*53668L)-k*12211;
    if(s1 < 0) s1 += Xm1;
    k = s2/52774L;
    s2 = Xa2*(s2-k*52774L)-k*3791;
    if(s2 < 0) s2 += Xm2;
    *(Xcg1+curntg-1) = s1;
    *(Xcg2+curntg-1) = s2;
    z = s1-s2;
    if(z < 1) z += (Xm1-1);
    if(*(Xqanti+curntg-1)) z = Xm1-z;
    ignlgi = z;
    return ignlgi;
#undef numg
}
