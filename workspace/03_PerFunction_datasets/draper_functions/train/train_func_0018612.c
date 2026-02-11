gen6_upload_color_calc_state(struct brw_context *brw)
{
   struct gl_context *ctx = &brw->ctx;
   struct gen6_color_calc_state *cc;

   cc = brw_state_batch(brw, AUB_TRACE_CC_STATE,
			sizeof(*cc), 64, &brw->cc.state_offset);
   memset(cc, 0, sizeof(*cc));


   cc->cc0.alpha_test_format = BRW_ALPHATEST_FORMAT_UNORM8;
   UNCLAMPED_FLOAT_TO_UBYTE(cc->cc1.alpha_ref_fi.ui, ctx->Color.AlphaRef);


   cc->cc0.stencil_ref = _mesa_get_stencil_ref(ctx, 0);
   cc->cc0.bf_stencil_ref = _mesa_get_stencil_ref(ctx, ctx->Stencil._BackFace);


   cc->constant_r = ctx->Color.BlendColorUnclamped[0];
   cc->constant_g = ctx->Color.BlendColorUnclamped[1];
   cc->constant_b = ctx->Color.BlendColorUnclamped[2];
   cc->constant_a = ctx->Color.BlendColorUnclamped[3];


   if (brw->gen == 6) {
      BEGIN_BATCH(4);
      OUT_BATCH(_3DSTATE_CC_STATE_POINTERS << 16 | (4 - 2));
      OUT_BATCH(0);
      OUT_BATCH(0);
      OUT_BATCH(brw->cc.state_offset | 1);
      ADVANCE_BATCH();
   } else {
      BEGIN_BATCH(2);
      OUT_BATCH(_3DSTATE_CC_STATE_POINTERS << 16 | (2 - 2));
      OUT_BATCH(brw->cc.state_offset | 1);
      ADVANCE_BATCH();
   }
}
