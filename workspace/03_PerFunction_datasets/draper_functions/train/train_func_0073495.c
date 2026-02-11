__free_dceauxlst(struct dceauxlst_t *dcehdr, int32 numinsts)
{
 register struct dceauxlst_t *dclp;
 register struct dcevnt_t *dcep2;
 struct dcevnt_t *dcep, *last_dcep;
 struct net_t *np;


  if (__optimized_sim) __misc_terr(__FILE__, __LINE__);


 for (dclp = dcehdr; dclp != NULL; dclp = dclp->dclnxt)
  {

   dcep = dclp->ldcep;


   np = dcep->dce_np;

   last_dcep = NULL;
   for (dcep2 = np->dcelst; dcep2 != NULL; dcep2 = dcep2->dcenxt)
    {
     if (dcep == dcep2)
      {
       if (last_dcep == NULL)
        {
         np->dcelst = dcep->dcenxt;


         if (np->dcelst == NULL)
          {

           np->nchg_has_dces = FALSE;
           if (np->nlds == NULL && !np->n_hasdvars)
            np->nchg_nd_chgstore = FALSE;

          }
        }
       else last_dcep->dcenxt = dcep->dcenxt;


       __free_dce_prevval(dcep, numinsts, __get_dcewid(dcep, np));


       if (dcep == __cbvc_causing_dcep) __cbvc_causing_dcep = NULL;

       __my_free((char *) dcep, sizeof(struct dcevnt_t));
       dcep = NULL;
       goto nxt_dce;
      }
     last_dcep = dcep2;
    }
   __misc_terr(__FILE__, __LINE__);
nxt_dce:;
  }

 __free_dceauxs_only(dcehdr);
}
