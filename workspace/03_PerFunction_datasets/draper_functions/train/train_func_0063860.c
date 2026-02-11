parse_u_longlist(lList **ppcmdline, const char *opt, lList **ppal, lList **value)
{
   bool ret = false;
   lListElem *ep = NULL;

   DENTER(TOP_LAYER, "parse_u_longlist");
   ep = lGetElemStr(*ppcmdline, SPA_switch, opt);
   if(ep != NULL) {
      *value = NULL;
      lXchgList(ep, SPA_argval_lListT, value);

      lRemoveElem(*ppcmdline, &ep);
      ret = true;
   }
   DRETURN(ret);
}
