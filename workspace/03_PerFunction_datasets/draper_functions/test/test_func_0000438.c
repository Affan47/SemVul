__exec_vpi_langlinecbs(char *lp, char *fnam, int32 lno)
{
 register i_tev_ndx tevpi;
 struct t_vpi_value wrk_val;
 struct t_vpi_languageline wrk_langlin;
 struct cbrec_t *cbp;
 struct t_cb_data wrk_cbdata, *datp;

 if ((tevpi = __vpicb_tehdri[cbLanguageLine]) == -1) return;

 datp = &wrk_cbdata;

 datp->time = NULL;
 datp->value = &wrk_val;
 datp->value->format = vpiStringVal;
 datp->value->value.misc = (char *) &wrk_langlin;
 wrk_langlin.linep = lp;
 wrk_langlin.file = fnam;
 wrk_langlin.lineno = lno;
 datp->obj = NULL;

 for (; tevpi != -1; tevpi = __tevtab[tevpi].tenxti)
  {

   if (__tevtab[tevpi].te_cancel) continue;

   cbp = __tevtab[tevpi].tu.tehp->hrec->hu.hcbp;
   datp->reason = cbp->cb_reason;
   datp->cb_rtn = cbp->cb_rtn;
   datp->user_data = cbp->cb_user_data;

   (*(datp->cb_rtn))(datp);
  }

}
