dcep_ref_mod(struct dcevnt_t *dcep)
{
 struct mod_t *ref_mdp;
 struct itree_t *itp;

 if (dcep->dce_xmrtyp == XNP_UPXMR || dcep->dce_xmrtyp == XNP_DOWNXMR)
  {
   ref_mdp = dcep->dceu.dcegrp->targmdp;
  }

 else if (dcep->dce_xmrtyp == XNP_RTXMR)
  {

   itp = dcep->dce_matchitp;
   ref_mdp = itp->itip->imsym->el.emdp;
  }
 else ref_mdp = __inst_mod;
 return(ref_mdp);
}
