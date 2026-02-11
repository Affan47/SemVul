st_cnt_modwires(struct mod_t *mdp, int32 *wires, int32 *wirebits,
 int32 *st_wires, int32 *st_wirebits)
{
 register int32 ni;
 register struct net_t *np;
 int32 mwires, mwirebits, st_mwires, st_mwirebits;

 mwires = 0;
 mwirebits = 0;
 st_mwires = 0;
 st_mwirebits = 0;
 if (mdp->mnnum != 0)
  {
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
    {

     if (np->iotyp != NON_IO) continue;
     if (np->ntyp >= NONWIRE_ST) continue;

     mwires++;
     mwirebits += np->nwid;
     if (!np->n_stren) continue;
     st_mwires++;
     st_mwirebits += np->nwid;
    }
  }
 *wires = mwires;
 *wirebits = mwirebits;
 *st_wires = st_mwires;
 *st_wirebits = st_mwirebits;
}
