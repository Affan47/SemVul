gen6_determine_sample_mask(struct brw_context *brw)
{
   struct gl_context *ctx = &brw->ctx;
   float coverage = 1.0;
   float coverage_invert = false;
   unsigned sample_mask = ~0u;

   unsigned num_samples = ctx->DrawBuffer->Visual.samples;

   if (ctx->Multisample._Enabled) {
      if (ctx->Multisample.SampleCoverage) {
         coverage = ctx->Multisample.SampleCoverageValue;
         coverage_invert = ctx->Multisample.SampleCoverageInvert;
      }
      if (ctx->Multisample.SampleMask) {
         sample_mask = ctx->Multisample.SampleMaskValue;
      }
   }

   if (num_samples > 1) {
      int coverage_int = (int) (num_samples * coverage + 0.5);
      uint32_t coverage_bits = (1 << coverage_int) - 1;
      if (coverage_invert)
         coverage_bits ^= (1 << num_samples) - 1;
      return coverage_bits & sample_mask;
   } else {
      return 1;
   }
}
