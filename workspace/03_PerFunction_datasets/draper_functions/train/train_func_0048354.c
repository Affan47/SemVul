brw_upload_initial_gpu_state(struct brw_context *brw)
{


   if (!brw->hw_ctx)
      return;

   brw_upload_invariant_state(brw);

   if (brw->gen >= 8) {
      gen8_emit_3dstate_sample_pattern(brw);
   }
}
