href_list_append_to_dstring(const lList *this_list, dstring *string)
{
   const char *const delim = " ";
   bool ret = true;

   DENTER(HOSTREF_LAYER, "href_list_append_to_dstring");
   if (this_list != NULL && string != NULL) {
      lListElem *href;
      bool is_first = true;

      for_each(href, this_list) {
         const char *name = lGetHost(href, HR_name);

         if (!is_first) {
            sge_dstring_append(string, delim);
         }
         sge_dstring_append(string, name);
         is_first = false;
      }
   } else {
      ret = false;
   }
   DEXIT;
   return ret;
}
