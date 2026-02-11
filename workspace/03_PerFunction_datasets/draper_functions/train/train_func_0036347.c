sizepasscover(a, hszp, dszp, long_bytes)
     A a;
     I *hszp, *dszp;
     long long_bytes;
{
  I rc=sizepass(a, hszp, dszp, long_bytes);
  if (ISMEGAHDR(*hszp)) (*hszp) += CDRMEGAHDRLENLEN;
  return(rc);
}
