sge_gdi_packet_create(sge_gdi_ctx_class_t * ctx, lList **answer_list)
{
   sge_gdi_packet_class_t *ret = NULL;

   DENTER(TOP_LAYER, "sge_gdi_packet_create");
   ret = sge_gdi_packet_create_base(answer_list);
   if (ret != NULL) {
      sge_gdi_packet_initialize_auth_info(ctx, ret);
   }
   DRETURN(ret);
}
