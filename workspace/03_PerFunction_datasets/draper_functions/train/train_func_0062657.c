bldndx_str(char *s, word32 ndx, word32 nstates)
{
 register word32 i;
 word32 val;
 char vs1[10];

 for (i = 0; i < nstates; i++)
  { val = (ndx >> (2*i)) & 3L; __to_uvvnam(vs1, val); s[i] = vs1[0]; }
 s[i] = '\0';
 return(s);
}
