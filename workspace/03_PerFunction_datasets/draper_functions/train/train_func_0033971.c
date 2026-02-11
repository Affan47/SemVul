getUserTemplate()
{
   lListElem *ep;

   DENTER(TOP_LAYER, "getUserTemplate");

   ep = lCreateElem(UU_Type);
   lSetString(ep, UU_name, "template");
   lSetString(ep, UU_default_project, NULL);
   lSetUlong(ep, UU_oticket, 0);
   lSetUlong(ep, UU_fshare, 0);
   lSetUlong(ep, UU_job_cnt, 0);
   lSetList(ep, UU_project, NULL);
   lSetList(ep, UU_usage, NULL);
   lSetList(ep, UU_long_term_usage, NULL);

   DEXIT;
   return ep;
}
