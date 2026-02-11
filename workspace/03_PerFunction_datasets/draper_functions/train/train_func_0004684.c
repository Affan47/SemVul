ulong_list_parse_from_string(lList **this_list, lList **answer_list,
                             const char *string, const char *delimitor)
{
   bool ret = true;

   DENTER(TOP_LAYER, "ulong_list_parse_from_string");
   if (this_list != NULL && string != NULL && delimitor != NULL) {
      struct saved_vars_s *context = NULL;
      const char *token;

      token = sge_strtok_r(string, delimitor, &context);
      while (token != NULL) {
         u_long32 value;

         ret = ulong_parse_from_string(&value, answer_list, token);
         if (ret) {
            lAddElemUlong(this_list, ULNG_value, value, ULNG_Type);
         } else {
            break;
         }
         token = sge_strtok_r(NULL, delimitor, &context);
      }
      sge_free_saved_vars(context);
   }
   DRETURN(ret);
}
