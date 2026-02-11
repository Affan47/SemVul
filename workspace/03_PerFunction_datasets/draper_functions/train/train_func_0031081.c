mark_sttypewires(void)
{
 register int32 syi;
 register struct mod_t *mdp;
 register struct net_t *np;
 register struct sy_t *syp;
 struct sy_t **syms;
 struct symtab_t *sytp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   sytp = mdp->msymtab;

   for (syi = 0, syms = sytp->stsyms; syi < (int32) sytp->numsyms; syi++)
    {
     syp = syms[syi];
     if (syp->sytyp != SYM_N) continue;
     np = syp->el.enp;


     switch ((byte) np->ntyp) {

      case N_TRIREG: case N_TRI0: case N_TRI1: case N_SUPPLY0:
      case N_SUPPLY1:
       np->n_stren = TRUE;
       mdp->mhassts = TRUE;
       __design_no_strens = FALSE;


       break;
     }
    }
  }
}
