exec_log_fnamchg(struct expr_t *axp)
{
 int32 slen;
 FILE *tmp_s;
 char *chp;

 if (axp == NULL) { __log_s = __save_log_s; return; }
 chp = __get_eval_cstr(axp->lu.x, &slen);
 if ((tmp_s = __tilde_fopen(chp, "w")) == NULL)
  {
   __sgferr(1243,
    "cannot open new $log output transcript file %s - not changed",
    __exprline);
   __my_free(chp, slen + 1);
   return;
  }
 if (__log_s != NULL && __log_s != stdout && __log_s != stderr)
  {
   __my_fclose(__log_s);
   __my_free(__log_fnam, strlen(__log_fnam) + 1);
   __log_fnam = NULL;
  }
 __log_fnam = chp;
 __log_s = tmp_s;
 __save_log_s = NULL;


 if (__verbose)
  __cv_msg("  Now writing output log to file \"%s\".\n", __log_fnam);
}
