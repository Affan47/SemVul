__exec_monit(struct dceauxlst_t *monit_hd, int32 force_write)
{
 int32 base, sav_slin_cnt, sav_sfnam_ind;
 struct tskcall_t *tkcp;
 struct expr_t *tkxp;
 struct systsk_t *stbp;


 if (__monit_stp == NULL) return;


 if (!chk_monits_chged(monit_hd) && !force_write) return;

 sav_slin_cnt = __slin_cnt;
 sav_sfnam_ind = __sfnam_ind;
 __slin_cnt = __monit_stp->stlin_cnt;
 __sfnam_ind = __monit_stp->stfnam_ind;

 tkcp = &(__monit_stp->st.stkc);
 tkxp = tkcp->tsksyx;
 stbp = tkxp->lu.sy->el.esytbp;

 __push_itstk(__monit_itp);

 switch (stbp->stsknum) {
  case STN_MONITOR: base = BDEC; goto nonf_write;
  case STN_MONITORH: base = BHEX; goto nonf_write;
  case STN_MONITORB: base = BBIN; goto nonf_write;
  case STN_MONITORO: base = BOCT;
nonf_write:
   __do_disp(tkcp->targs, base);
   __cvsim_msg("\n");
   break;
  case STN_FMONITOR: base = BDEC; goto f_disp;
  case STN_FMONITORB: base = BBIN; goto f_disp;
  case STN_FMONITORH: base = BHEX; goto f_disp;
  case STN_FMONITORO: base = BOCT;
f_disp:
   __fio_do_disp(tkcp->targs, base, TRUE, tkxp->lu.sy->synam);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 __pop_itstk();
 __slin_cnt = sav_slin_cnt;
 __sfnam_ind = sav_sfnam_ind;
}
