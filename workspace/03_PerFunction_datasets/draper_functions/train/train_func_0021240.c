disp_stvar(struct net_t *np, int32 i1, int32 i2)
{
 register int32 i;
 char s1[RECLEN];

 if (i1 == -1) { i1 = np->nwid - 1; i2 = 0; }

 for (i = i1; i >= i2; i--)
  {
   __adds(__to_vvstnam(s1, (word32) np->nva.bp[i]));
   if (i > i2) addch_(' ');
  }
 __exprline[__cur_sofs] = '\0';
}
