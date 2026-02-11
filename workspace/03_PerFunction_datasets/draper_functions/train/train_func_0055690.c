__v64_to_real(double *d1, word64 *tim)
{
 int32 good;
 register word32 w0, w1, mask;
 double dbase;


 w0 = (word32) ((*tim) & WORDMASK_ULL);
 w1 = (word32) (((*tim) >> 32) & WORDMASK_ULL);
 if (w1 == 0L) { *d1 = (double) w0; return(TRUE); }

 good = TRUE;

 mask = __masktab[WBITS - (_DEXPLEN + 1)];
 if ((w1 & ~mask) != 0L) good = FALSE;
 dbase = ((double) (0xffffffff)) + 1.0;


 *d1 = (double) w0 + dbase*((double) w1);
 return(good);
}
