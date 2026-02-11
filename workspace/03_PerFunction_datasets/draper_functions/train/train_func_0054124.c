ttscale(U16B con) {

    ttab[con][0]>>=1;
    if (ttab[con][0]==0) ttab[con][0]=1;
    ttab[con][1]>>=1;
    if (ttab[con][1]==0) ttab[con][1]=1;
}
