set_alloutpths_dels(char *qualport, int32 pi1, int32 pi2,
 struct itree_t *itp, struct mod_t *ctmdp)
{
 register struct spcpth_t *pthp;
 register struct pthlst_t *plp;
 int32 pei;
 struct pthlst_t *plhd, *plend;
 struct itree_t *cor_itp, *itp2;
 struct mod_t *mdp;
 struct pathel_t *pep;
 char portnam[IDLEN];


 if (itp == NULL)
  {
   if ((cor_itp = find_1under_itp(ctmdp)) == NULL)
    {
     __pv_fwarn(669,
      "delays not changed for (DEVICE portinst %s because no instance of type %s in context",
      qualport, ctmdp->msym->synam);
     return;
    }
  }
 else cor_itp = itp;


 if (!xtrct_portdev(&itp2, portnam, qualport, cor_itp, "DEVICE", "PORT"))
  return;
 mdp = itp2->itip->imsym->el.emdp;

 if (ctmdp->mspfy == NULL || ctmdp->mspfy->spcpths == NULL)
  {
   not_a_port(portnam, IO_OUT, mdp, "(DEVICE");
   __pv_fwarn(668,
    "SDF DEVICE module CELLTYPE %s has no paths - nothing to do",
    ctmdp->msym->synam);
   return;
  }
 plhd = plend = NULL;
 for (pthp = ctmdp->mspfy->spcpths; pthp != NULL; pthp = pthp->spcpthnxt)
  {

   for (pei = 0; pei <= pthp->last_peout; pei++)
    {
     pep = &(pthp->peouts[pei]);
     if (strcmp(pep->penp->nsym->synam, portnam) != 0) continue;

     if (pi1 != -1 && pep->pthi1 != -1)
      { if (pi1 > pep->pthi1 && pi2 < pep->pthi2) continue; }


     if (pi1 == -1 || pep->pthi1 == -1
      || (pi1 <= pep->pthi1 && pi1 >= pep->pthi2)
      || (pi2 <= pep->pthi1 && pi2 >= pep->pthi2))
      {
       plp = (struct pthlst_t *) __my_malloc(sizeof(struct pthlst_t));
       plp->lpthp = pthp;
       plp->pthlnxt = NULL;
       if (plend == NULL) plhd = plend = plp;
       else { plend->pthlnxt = plp; plend = plp; }


       goto nxt_pth;
      }
    }
nxt_pth:;
  }
 if (plhd == NULL)
  {
   if (not_a_port(portnam, IO_OUT, mdp, "(DEVICE")) return;

   __pv_ferr(1329,
    "for (DEVICE no module %s specify path ends on output/inout port %s",
    mdp->msym->synam, portnam);
   return;
  }
 for (plp = plhd; plp != NULL; plp = plp->pthlnxt)
  set_1pthdel(plp, itp, ctmdp);
 free_pthlst(plhd);
}
