phrtsd(char* phrase,long *seed1,long *seed2)


{

static char table[] =
"abcdefghijklmnopqrstuvwxyz\
ABCDEFGHIJKLMNOPQRSTUVWXYZ\
0123456789\
!@#$%^&*()_+[];:'\\\"<>?,./";

long ix;

static long twop30 = 1073741824L;
static long shift[5] = {
    1L,64L,4096L,262144L,16777216L
};
static long i,ichr,j,lphr,values[5];
extern long lennob(char *str);

    *seed1 = 1234567890L;
    *seed2 = 123456789L;
    lphr = lennob(phrase);
    if(lphr < 1) return;
    for(i=0; i<=(lphr-1); i++) {
	for (ix=0; table[ix]; ix++) if (*(phrase+i) == table[ix]) break;

	ix++;
        if (!table[ix]) ix = 0;
        ichr = ix % 64;
        if(ichr == 0) ichr = 63;
        for(j=1; j<=5; j++) {
            *(values+j-1) = ichr-j;
            if(*(values+j-1) < 1) *(values+j-1) += 63;
        }
        for(j=1; j<=5; j++) {
            *seed1 = ( *seed1+*(shift+j-1)**(values+j-1) ) % twop30;
            *seed2 = ( *seed2+*(shift+j-1)**(values+6-j-1) )  % twop30;
        }
    }
}
