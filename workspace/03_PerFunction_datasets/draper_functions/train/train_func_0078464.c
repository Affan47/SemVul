build_rule_error(struct cfg_t *cfgp, struct cfglib_t *cntxt_lbp,
 struct cfgrule_t *rulp)
{


 if (rulp->rultyp == CFG_INSTANCE)
  {
   __pv_err(3576, "config %s at %s: unable to bind rule - no such module %s",
    cfgp->cfgnam, __cfg_lineloc(__xs, cfgp->cfg_fnam, rulp->rul_lno),
    rulp->objnam);
  }
 else if (rulp->rultyp == CFG_CELL)
  {
   if (rulp->libnam != NULL)
    {

     __pv_err(3576,
      "config %s at %s: unable to bind rule - no such cell %s",
      cfgp->cfgnam, __cfg_lineloc(__xs, cfgp->cfg_fnam, rulp->rul_lno),
      rulp->objnam);
    }
  }
}
