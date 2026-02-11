_mesa_get_min_invocations_per_fragment(struct gl_context *ctx,
                                       const struct gl_fragment_program *prog,
                                       bool ignore_sample_qualifier)
{


   if (ctx->Multisample.Enabled) {


      if (prog->IsSample && !ignore_sample_qualifier)
         return MAX2(ctx->DrawBuffer->Visual.samples, 1);

      if (prog->Base.SystemValuesRead & (SYSTEM_BIT_SAMPLE_ID |
                                         SYSTEM_BIT_SAMPLE_POS))
         return MAX2(ctx->DrawBuffer->Visual.samples, 1);
      else if (ctx->Multisample.SampleShading)
         return MAX2(ceil(ctx->Multisample.MinSampleShadingValue *
                          ctx->DrawBuffer->Visual.samples), 1);
      else
         return 1;
   }
   return 1;
}
