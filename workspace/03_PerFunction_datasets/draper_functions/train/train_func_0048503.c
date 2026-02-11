sge_gdi2_is_done(sge_gdi_ctx_class_t* ctx, lList **alpp, state_gdi_multi *state)
{
   bool ret = true;

   DENTER(GDI_LAYER, "sge_gdi2_is_done");
   if (state->packet != NULL) {
      ret = sge_gdi_packet_is_handled(state->packet);
   }
   DRETURN(ret);
}
