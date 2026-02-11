store_regex(LEX *lc, RES_ITEM *item, int index, int pass)
{
   int token, rc;
   regex_t preg;
   char prbuf[500];
   const char *type;
   int newsize;

   token = lex_get_token(lc, T_SKIP_EOL);
   if (pass == 1) {


      switch (token) {
      case T_IDENTIFIER:
      case T_UNQUOTED_STRING:
      case T_QUOTED_STRING:
         rc = regcomp(&preg, lc->str, REG_EXTENDED);
         if (rc != 0) {
            regerror(rc, &preg, prbuf, sizeof(prbuf));
            regfree(&preg);
            scan_err1(lc, _("Regex compile error. ERR=%s\n"), prbuf);
            break;
         }
         regfree(&preg);
         if (item->code == 1) {
            type = "regexdir";
            res_incexe.current_opts->regexdir.append(bstrdup(lc->str));
            newsize = res_incexe.current_opts->regexdir.size();
         } else if (item->code == 2) {
            type = "regexfile";
            res_incexe.current_opts->regexfile.append(bstrdup(lc->str));
            newsize = res_incexe.current_opts->regexfile.size();
         } else {
            type = "regex";
            res_incexe.current_opts->regex.append(bstrdup(lc->str));
            newsize = res_incexe.current_opts->regex.size();
         }
         Dmsg4(900, "set %s %p size=%d %s\n",
            type, res_incexe.current_opts, newsize, lc->str);
         break;
      default:
         scan_err1(lc, _("Expected a regex string, got: %s\n"), lc->str);
      }
   }
   scan_to_eol(lc);
}
