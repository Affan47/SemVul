update_reschedule_unknown_timout_values(const char *config_name)
{
   lListElem *host = NULL;
   lList *master_exechost_list = *object_type_get_master_list(SGE_TYPE_EXECHOST);

   DENTER(TOP_LAYER, "update_reschedule_unknown_timout_values");

   if (strcmp(SGE_GLOBAL_NAME, config_name) == 0) {
      lListElem *global_exechost_elem   = NULL;
      lListElem *template_exechost_elem = NULL;

      global_exechost_elem   = host_list_locate(master_exechost_list, SGE_GLOBAL_NAME);
      template_exechost_elem = host_list_locate(master_exechost_list, SGE_TEMPLATE_NAME);

      for_each(host, master_exechost_list) {
         if ((host != global_exechost_elem) && (host != template_exechost_elem)) {
            update_reschedule_unknown_timeout(host);
         }
      }
   } else if (strcmp(SGE_TEMPLATE_NAME, config_name) != 0 ) {
      host = host_list_locate(master_exechost_list, config_name);
      update_reschedule_unknown_timeout(host);
   }

   DRETURN_VOID;
}
