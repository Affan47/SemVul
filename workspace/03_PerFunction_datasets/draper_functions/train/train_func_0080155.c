udpiodecl_get(struct h_t *hp, int32 prop)
{
 int32 pval;
 struct mod_t *mdp;
 struct mod_pin_t *mpp;

 mdp = hp->hin_itp->itip->imsym->el.emdp;
 mpp = &(mdp->mpins[hp->hrec->hu.hpi]);
 pval = vpiUndefined;
 switch (prop) {
  case vpiDirection:
   if (mpp->mptyp == IO_IN) pval = vpiInput;
   else if (mpp->mptyp == IO_OUT) pval = vpiOutput;
   else __vpi_terr(__FILE__, __LINE__);
   break;
  case vpiLineNo:
   pval = mpp->mplin_cnt;
   break;
  case vpiSize:
   pval = 1;
   break;
  case vpiScalar:
   pval = TRUE;
   break;
  case vpiVector:
   pval = FALSE;
   break;
  default: notpropof_err(hp->hrec->htyp, prop);
 }
 return(pval);
}
