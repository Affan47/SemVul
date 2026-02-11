portstrprop_vpiget(struct h_t *hp, int32 prop)
{
 struct mod_t *mdp;
 struct mod_pin_t *mpp;

 mdp = hp->hin_itp->itip->imsym->el.emdp;
 mpp = &(mdp->mpins[hp->hrec->hu.hpi]);
 switch (prop) {
  case vpiFile:
   strcpy(__wrk_vpiget_str, __in_fils[mpp->mpfnam_ind]);
   break;
  case vpiName:
   if (mpp->mpsnam == NULL) return(NULL);
   return(mpp->mpsnam);
  default: __notstrpropof_err(hp->hrec->htyp, prop); return(NULL);
 }
 return(__wrk_vpiget_str);
}
