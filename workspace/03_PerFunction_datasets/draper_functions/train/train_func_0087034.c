findmatch_term_vcl_dce(struct h_t *hp,
 int32 (*consumer)(), char *user_data)
{
 register int32 tevpi;
 int32 gi, cv;
 struct gate_t *gp;
 struct mod_t *mdp;
 struct cbrec_t *cbp;
 struct vclrec_t *vclp;
 struct h_t *hp2;


 gp = hp->hrec->hu.hgp;
 mdp = hp->hin_itp->itip->imsym->el.emdp;
 gi = gp - mdp->mgates;
 if (mdp->mgateout_cbs == NULL || mdp->mgateout_cbs[gi] == NULL)
  return(NULL);
 if ((tevpi = mdp->mgateout_cbs[gi][hp->hin_itp->itinum]) == -1)
  return(NULL);

 for (; tevpi != -1; tevpi = __tevtab[tevpi].tenxti)
  {


   if (__tevtab[tevpi].te_cancel) continue;

   cbp = __tevtab[tevpi].tu.tehp->hrec->hu.hcbp;

   if (cbp->cb_rtn != exec_acc_gateout_vclcb) continue;


   vclp = (struct vclrec_t *) cbp->cb_user_data;


   if ((struct h_t *) vclp->vclobj != hp) continue;
   if (vclp->vcl_cb_rtn != consumer) continue;
   if (vclp->vcl_udata != user_data) continue;

   hp2 = (struct h_t *) vclp->vclobj;
   __acc_vpi_erroff = TRUE;
   cv = vpi_compare_objects((vpiHandle) hp, (vpiHandle) hp2);

   if (__my_vpi_chk_error())
    {
     __acc_err(1754,
      "acc_vcl_add problem comparing other added primitive output terminal vcl object %s",
       to_acc_onam(__wrks1, hp2->hrec->htyp));
     continue;
    }

   if (cv == 0) continue;
   return(vclp);
  }
 return(NULL);
}
