upload_ps_state(struct brw_context *brw)
{
   struct gl_context *ctx = &brw->ctx;
   uint32_t dw3 = 0, dw6 = 0, dw7 = 0;


   BEGIN_BATCH(2);
   OUT_BATCH(_3DSTATE_BINDING_TABLE_POINTERS_PS << 16 | (2 - 2));
   OUT_BATCH(brw->wm.base.bind_bo_offset);
   ADVANCE_BATCH();


   BEGIN_BATCH(2);
   OUT_BATCH(_3DSTATE_SAMPLER_STATE_POINTERS_PS << 16 | (2 - 2));
   OUT_BATCH(brw->wm.base.sampler_offset);
   ADVANCE_BATCH();


   gen8_upload_constant_state(brw, &brw->wm.base, true, _3DSTATE_CONSTANT_PS);


   dw3 |= GEN7_PS_VECTOR_MASK_ENABLE;


   dw3 |=
      (ALIGN(brw->wm.base.sampler_count, 4) / 4) << GEN7_PS_SAMPLER_COUNT_SHIFT;


   dw3 |=
      ((brw->wm.prog_data->base.binding_table.size_bytes / 4) <<
       GEN7_PS_BINDING_TABLE_ENTRY_COUNT_SHIFT);


   if (ctx->Shader.CurrentProgram[MESA_SHADER_FRAGMENT] == NULL)
      dw3 |= GEN7_PS_FLOATING_POINT_MODE_ALT;

   dw6 |= (brw->max_wm_threads - 2) << HSW_PS_MAX_THREADS_SHIFT;


   if (brw->wm.prog_data->nr_params > 0)
      dw6 |= GEN7_PS_PUSH_CONSTANT_ENABLE;

   dw6 |= GEN7_PS_8_DISPATCH_ENABLE;
   if (brw->wm.prog_data->prog_offset_16)
      dw6 |= GEN7_PS_16_DISPATCH_ENABLE;

   dw7 |=
      brw->wm.prog_data->first_curbe_grf << GEN7_PS_DISPATCH_START_GRF_SHIFT_0 |
      brw->wm.prog_data->first_curbe_grf_16<< GEN7_PS_DISPATCH_START_GRF_SHIFT_2;

   BEGIN_BATCH(12);
   OUT_BATCH(_3DSTATE_PS << 16 | (12 - 2));
   OUT_BATCH(brw->wm.base.prog_offset);
   OUT_BATCH(0);
   OUT_BATCH(dw3);
   if (brw->wm.prog_data->total_scratch) {
      OUT_RELOC64(brw->wm.base.scratch_bo,
                  I915_GEM_DOMAIN_RENDER, I915_GEM_DOMAIN_RENDER,
                  ffs(brw->wm.prog_data->total_scratch) - 11);
   } else {
      OUT_BATCH(0);
      OUT_BATCH(0);
   }
   OUT_BATCH(dw6);
   OUT_BATCH(dw7);
   OUT_BATCH(0);
   OUT_BATCH(0);
   OUT_BATCH(brw->wm.base.prog_offset + brw->wm.prog_data->prog_offset_16);
   OUT_BATCH(0);
   ADVANCE_BATCH();
}
