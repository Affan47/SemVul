jsv_split_token(dstring *input, dstring *token, dstring *args)
{
   const char *i = sge_dstring_get_string(input);
   bool ret = true;

   DENTER(TOP_LAYER, "jsv_split_token");
   if (i != NULL) {
      struct saved_vars_s *cntx = NULL;
      const char *token1 = sge_strtok_r(i, " ", &cntx);

      if (token1 != NULL) {
         bool first = true;
         const char *arg = NULL;

         sge_dstring_append(token, token1);
         arg = sge_strtok_r(NULL, " ", &cntx);
         while (arg != NULL) {
            if (first) {
               first = false;
            } else {
               sge_dstring_append(args, " ");
            }
            sge_dstring_append(args, arg);
            arg = sge_strtok_r(NULL, " ", &cntx);
         }
      }
      sge_free_saved_vars(cntx);
   }
   DRETURN(ret);
}
