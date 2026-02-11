upload_wm_state(struct brw_context *brw)
{
   struct gl_context *ctx = &brw->ctx;
   uint32_t dw1 = 0;

   dw1 |= GEN7_WM_STATISTICS_ENABLE;
   dw1 |= GEN7_WM_LINE_AA_WIDTH_1_0;
   dw1 |= GEN7_WM_LINE_END_CAP_AA_WIDTH_0_5;
   dw1 |= GEN7_WM_POINT_RASTRULE_UPPER_RIGHT;


   if (ctx->Line.StippleFlag)
      dw1 |= GEN7_WM_LINE_STIPPLE_ENABLE;


   if (ctx->Polygon.StippleFlag)
      dw1 |= GEN7_WM_POLYGON_STIPPLE_ENABLE;


   dw1 |= brw->wm.prog_data->barycentric_interp_modes <<
      GEN7_WM_BARYCENTRIC_INTERPOLATION_MODE_SHIFT;

   BEGIN_BATCH(2);
   OUT_BATCH(_3DSTATE_WM << 16 | (2 - 2));
   OUT_BATCH(dw1);
   ADVANCE_BATCH();
}
