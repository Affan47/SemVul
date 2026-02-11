qrstat_report_ar_node_string(qrstat_report_handler_t* handler, lList **alpp,
                                 const char *name, const char *value)
{
   bool ret = true;
   dstring *buffer = (dstring*)handler->ctx;

   DENTER(TOP_LAYER, "qrstat_report_ar_node_string");

   if (value != NULL) {
      sge_dstring_sprintf_append(buffer, "      <"SFN">"SFN"</"SFN">\n", name, value, name);
   } else {
      sge_dstring_sprintf_append(buffer, "      <"SFN"/>\n", name);
   }

   DRETURN(ret);
}
