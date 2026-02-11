DumpConstants(const Proto* tf, FILE* D)
{
 int i,n;
 DumpInt(n=tf->nkstr,D);
 for (i=0; i<n; i++)
  DumpString(tf->kstr[i],D);
 DumpInt(tf->nknum,D);
 DumpVector(tf->knum,tf->nknum,sizeof(*tf->knum),D);
 DumpInt(n=tf->nkproto,D);
 for (i=0; i<n; i++)
  DumpFunction(tf->kproto[i],D);
}
