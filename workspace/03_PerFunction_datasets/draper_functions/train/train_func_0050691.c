std_chg_mos_gate(register struct gate_t *gp, register word32 i)
{
 register int32 out_chg, gid;


 if (!chg_mos_instate(gp, i))
  { if (__ev_tracing) trace_gunchg(gp, i); return; }

 out_chg = TRUE;
 gid = gp->gmsym->el.eprimp->gateid;
 switch (gid) {
  case G_NMOS: __eval_nmos_gate(gp->gstate.wp[__inum]); break;
  case G_RNMOS: __eval_rnmos_gate(gp->gstate.wp[__inum]); break;
  case G_PMOS: __eval_pmos_gate(gp->gstate.wp[__inum]); break;
  case G_RPMOS: __eval_rpmos_gate(gp->gstate.wp[__inum]); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 if (__new_gateval == __old_gateval) out_chg = FALSE;

 if (__ev_tracing) evtr_prop_gatechg(gp, i, out_chg);
 else
  {
   if (gp->g_delrep == DT_NONE)
    { if (out_chg) change_gate_outwire(gp); return; }
   prop_gatechg(gp, out_chg, FALSE);
  }
}
