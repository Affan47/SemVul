bld1_xdvval(register struct net_t *np, char *dvcodp)
{
 __cur_sofs = 0;
 if (!np->n_isavec)
  { if (np->ntyp == N_EVENT) addch_('1'); else addch_('x'); }

 else if (np->ntyp == N_REAL) __adds("r0.0 ");
 else __adds("bx ");
 __adds(dvcodp);
}
