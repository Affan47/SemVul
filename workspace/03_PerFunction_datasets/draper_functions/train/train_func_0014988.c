__em_suppr(int32 id)
{
 word32 w;
 int32 bi, wi;

 bi = id % WBITS;
 wi = id / WBITS;
 w = __wsupptab[wi];
 if ((w & (1L << bi)) != 0) return(TRUE);
 return(FALSE);
}
