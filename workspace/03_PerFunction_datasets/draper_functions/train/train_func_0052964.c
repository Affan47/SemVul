chk_dctrl(struct delctrl_t *dctp)
{
 int32 sav_ecnt;
 struct paramlst_t *dhdr;


 if (dctp->dctyp == DC_EVENT || dctp->dctyp == DC_RHSEVENT)
  {

   if (!dctp->implicit_evxlst)
    {
     __chk_evxpr(dctp->dc_du.pdels->plxndp);
    }
  }


 else
  {
   dhdr = __copy_dellst(dctp->dc_du.pdels);
   __chk_delparams(dhdr, "procedural delay control", FALSE);
   __free_dellst(dhdr);
  }

 if (dctp->repcntx != NULL)
  {
   __chk_rhsexpr(dctp->repcntx, 0);

   if (dctp->repcntx->szu.xclen > WBITS)
    {
     __sgfwarn(543,
      "truncation of right hand side event control repeat count from %d to 32 bits - high bits ignored",
      dctp->repcntx->szu.xclen);
    }
  }

 sav_ecnt = __pv_err_cnt;


 if (dctp->actionst != NULL) __chk_lstofsts(dctp->actionst);


 if (dctp->implicit_evxlst)
  {

   if (sav_ecnt > __pv_err_cnt)
    {
     __sgfwarn(3134, "implicit @(*) event control action statement has syntax errors - can't build implicit change list");
     __bld_unc_expr();
     dctp->dc_du.pdels->plxndp = __root_ndp;
     return;
    }
   if (dctp->actionst == NULL)
    {
     __sgfwarn(3135, "implicit @(*) event control no action statement - no implicit change list");
     __bld_unc_expr();
     dctp->dc_du.pdels->plxndp = __root_ndp;
     return;
    }


   __impl_evlst_hd = __impl_evlst_tail = NULL;
   bld_stlst_evxlst(dctp->actionst);
   if (__impl_evlst_hd != NULL)
    {
     dctp->dc_du.pdels->plxndp = bld_evlst_comma_expr();
     __impl_evlst_hd = __impl_evlst_tail = NULL;


    }
  }
}
