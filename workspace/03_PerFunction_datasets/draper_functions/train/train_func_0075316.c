var_list_copy_prefix_vars_undef(lList **varl,
                                     const lList *src_varl,
                                     const char *prefix,
                                     const char *new_prefix)
{
   int prefix_len = strlen(prefix);
   lListElem *var_elem = NULL;
   lList *var_list2 = NULL;

   DENTER(TOP_LAYER, "var_list_copy_prefix_vars");
   for_each(var_elem, src_varl) {
      const char *prefix_name = lGetString(var_elem, VA_variable);

      if (!strncmp(prefix_name, prefix, prefix_len)) {
         char name[MAX_STRING_SIZE];
         const char *value = lGetString(var_elem, VA_value);
         const char *name_without_prefix = &prefix_name[prefix_len];
         lListElem *existing_variable;

         sprintf(name, "%s%s", new_prefix, name_without_prefix);
         existing_variable = lGetElemStr(*varl, VA_variable, name);
         if (existing_variable == NULL) {
            var_list_set_string(&var_list2, name, value);
         }
      }
   }
   if (*varl == NULL) {
      *varl = lCreateList("", VA_Type);
   }
   lAddList(*varl, &var_list2);
   DEXIT;
}
