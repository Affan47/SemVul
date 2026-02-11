qrstat_report_granted_parallel_environment_node(qrstat_report_handler_t* handler,
                                                    lList **alpp,
                                                    const char *name, const char *slots_range)
{
   bool ret = true;
   dstring *buffer = (dstring*)handler->ctx;

   DENTER(TOP_LAYER, "qrstat_report_granted_granted_parallel_environment_node");

   sge_dstring_sprintf_append(buffer, "         <parallel_environment>"SFN"</parallel_environment>\n", (name != NULL) ? name : "");
   sge_dstring_sprintf_append(buffer, "         <slots>"SFN"</slots>\n", (slots_range != NULL) ? slots_range : "");

   DRETURN(ret);
}
