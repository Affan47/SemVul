host_list_merge(lList *this_list)
{
   bool ret = true;

   DENTER(TOP_LAYER, "host_list_merge");

   if (this_list != NULL) {
      lListElem *global_host;


      global_host = lGetElemHost(this_list, EH_name, SGE_GLOBAL_NAME);
      if (global_host != NULL) {
         lListElem *host;


         lSetList(global_host, EH_merged_report_variables,
                  lCopyList("", lGetList(global_host, EH_report_variables)));


         for_each (host, this_list) {
            if (host != global_host) {

               if (!host_merge(host, global_host)) {
                  ret = false;
               }
            }
         }
      }
   }

   DRETURN(ret);
}
