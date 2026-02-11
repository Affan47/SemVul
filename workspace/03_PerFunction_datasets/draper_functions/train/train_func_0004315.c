bld_inst_iterator(struct h_t *hp)
{
 register int32 ii;
 register struct hrec_t *hrp2;
 register struct h_t *hp2;
 struct mod_t *mdp;
 struct itree_t *itp, *itp2;
 vpiHandle ihref;
 struct pviter_t *iterp;

 if (hp->hrec->htyp != vpiModule)
  { mustbe_inmoditer_err(vpiModule, hp); return(NULL); }
 itp = hp->hin_itp;
 mdp = itp->itip->imsym->el.emdp;
 if (mdp->minum <= 0) return(NULL);
 iterp = __alloc_iter(mdp->minum, &ihref);
 for (ii = 0; ii < mdp->minum; ii++)
  {
   hp2 = &(iterp->scanhtab[ii]);
   hrp2 = hp2->hrec;
   hrp2->htyp = vpiModule;
   itp2 = &(itp->in_its[ii]);
   hrp2->hu.hmdp = itp2->itip->imsym->el.emdp;
   hp2->hin_itp = itp2;
  }
 return(ihref);
}
