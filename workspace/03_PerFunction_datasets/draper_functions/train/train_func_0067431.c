bld3vndx_str(char *s, word32 ndx, word32 nstates)
{
 register word32 i;
 word32 val;
 char s1[10];

 for (i = 0; i < nstates; i++)
  { val = ndx % 3; ndx /= 3; __to_uvvnam(s1, val); s[i] = s1[0]; }
 s[i] = '\0';
 return(s);
}
