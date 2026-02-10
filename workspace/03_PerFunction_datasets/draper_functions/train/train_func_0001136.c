sge_unparse_checkpoint_option(
lListElem *job,
lList **pcmdline,
lList **alpp
) {
   lListElem *ep_opt = NULL;
   char *cp;
   int i;
   char str[1024 + 1];
   u_long32 ul;

   DENTER(TOP_LAYER, "sge_unparse_checkpoint_option");

   if ((i = lGetUlong(job, JB_checkpoint_attr))) {
      if ((cp = sge_unparse_checkpoint_attr(i, str))) {
         ep_opt = sge_add_arg(pcmdline, 0, lIntT, "-c", cp);
         lSetInt(ep_opt, SPA_argval_lIntT, i);
      }
      else {
         sprintf(str, MSG_JOB_INVALIDVALUEFORCHECKPOINTATTRIBINJOB_U,
            sge_u32c(lGetUlong(job, JB_job_number)));
         answer_list_add(alpp, str, STATUS_ESYNTAX, ANSWER_QUALITY_ERROR);
         return -1;
      }
   }

   if ((ul = lGetUlong(job, JB_checkpoint_interval))) {
      sprintf(str, sge_uu32, ul);
      ep_opt = sge_add_arg(pcmdline, c_OPT, lLongT, "-c", str);
      lSetLong(ep_opt, SPA_argval_lLongT, (long) ul);
   }

   DEXIT;
   return 0;
}
