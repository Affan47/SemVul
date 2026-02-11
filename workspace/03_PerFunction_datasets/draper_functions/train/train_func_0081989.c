sge_parse_cmdline_qrdel(char **argv, char **envp, lList **ppcmdline, lList **alpp) {
   char **sp;
   char **rp;

   DENTER(TOP_LAYER, "sge_parse_cmdline_qrdel");

   rp = argv;
   while (*(sp=rp)) {

      if ((rp = parse_noopt(sp, "-help", NULL, ppcmdline, alpp)) != sp)
         continue;


      if ((rp = parse_noopt(sp, "-f", "--force", ppcmdline, alpp)) != sp)
         continue;


      if (!strcmp("-u", *sp)) {
         lList *user_list = NULL;
         lListElem *ep_opt;

         sp++;
         if (*sp) {
            str_list_parse_from_string(&user_list, *sp, ",");

            ep_opt = sge_add_arg(ppcmdline, 0, lListT, *(sp - 1), *sp);
            lSetList(ep_opt, SPA_argval_lListT, user_list);
            sp++;
         }
         rp = sp;
         continue;
      }

      if ((rp = parse_param(sp, "ars", ppcmdline, alpp)) != sp) {
         continue;
      }

      answer_list_add_sprintf(alpp, STATUS_ESEMANTIC, ANSWER_QUALITY_ERROR,
                              MSG_PARSE_INVALIDOPTIONARGUMENTX_S, *sp);
      sge_usage(QRDEL, stderr);
      DRETURN(false);
   }

   DRETURN(true);
}
