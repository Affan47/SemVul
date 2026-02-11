dump_send_info(const char* comp_host, const char* comp_name, int comp_id, cl_xml_ack_type_t ack_type,
                          unsigned long tag, unsigned long* mid)
{
   char buffer[512];
   dstring ds;

   DENTER(GDI_LAYER, "dump_send_info");
   sge_dstring_init(&ds, buffer, sizeof(buffer));

   if (comp_host != NULL && comp_name != NULL) {
      DEBUG((SGE_EVENT,">>>>>>>>>>>>>>>>>>>>"));
      DEBUG((SGE_EVENT,"gdi_snd: sending message to %s/%s/"sge_U32CFormat": ",
               (char*)comp_host,comp_name ,sge_u32c(comp_id)));
      DEBUG((SGE_EVENT,"gdi_snd: cl_xml_ack_type_t: %s",            cl_com_get_mih_mat_string(ack_type)));
      DEBUG((SGE_EVENT,"gdi_snd: message tag:       %s",            sge_dump_message_tag( tag) ));
      if (mid) {
         DEBUG((SGE_EVENT,"gdi_snd: message id:        "sge_U32CFormat"",  sge_u32c(*mid) ));
      } else {
         DEBUG((SGE_EVENT,"gdi_snd: message id:        not handled by caller"));
      }
      DEBUG((SGE_EVENT,"gdi_snd: send time:         %s", sge_ctime(0, &ds)));
      DEBUG((SGE_EVENT,">>>>>>>>>>>>>>>>>>>>"));
   } else {
      DEBUG((SGE_EVENT,">>>>>>>>>>>>>>>>>>>>"));
      DEBUG((SGE_EVENT,"gdi_snd: some parameters are not set"));
      DEBUG((SGE_EVENT,">>>>>>>>>>>>>>>>>>>>"));
   }
   DEXIT;
}
