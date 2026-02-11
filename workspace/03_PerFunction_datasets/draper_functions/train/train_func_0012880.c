var_list_parse_from_string(lList **lpp, const char *variable_str,
                               int check_environment)
{
   char *variable;
   char *val_str;
   int var_len;
   char **str_str;
   char **pstr;
   lListElem *ep;
   char *va_string;

   DENTER(TOP_LAYER, "var_list_parse_from_string");

   if (!lpp) {
      DEXIT;
      return 1;
   }

   va_string = sge_strdup(NULL, variable_str);
   if (!va_string) {
      *lpp = NULL;
      DEXIT;
      return 2;
   }
   str_str = string_list(va_string, ",", NULL);
   if (!str_str || !*str_str) {
      *lpp = NULL;
      FREE(va_string);
      DEXIT;
      return 3;
   }

   if (!*lpp) {
      *lpp = lCreateList("variable list", VA_Type);
      if (!*lpp) {
         FREE(va_string);
         FREE(str_str);
         DEXIT;
         return 4;
      }
   }

   for (pstr = str_str; *pstr; pstr++) {
      struct saved_vars_s *context;
      ep = lCreateElem(VA_Type);

      lAppendElem(*lpp, ep);

      context = NULL;
      variable = sge_strtok_r(*pstr, "=", &context);
      SGE_ASSERT((variable));
      var_len=strlen(variable);
      lSetString(ep, VA_variable, variable);
      val_str=*pstr;


      if (val_str[var_len] == '=') {
          lSetString(ep, VA_value, &val_str[var_len+1]);
      } else if (check_environment) {
         lSetString(ep, VA_value, sge_getenv(variable));
      } else {
         lSetString(ep, VA_value, NULL);
      }
      sge_free_saved_vars(context);
   }
   FREE(va_string);
   FREE(str_str);
   DRETURN(0);
}
