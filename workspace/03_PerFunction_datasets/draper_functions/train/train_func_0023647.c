lp_build_rgba8_to_fi32_soa(struct gallivm_state *gallivm,
                           struct lp_type dst_type,
                           LLVMValueRef packed,
                           LLVMValueRef *rgba)
{
   LLVMBuilderRef builder = gallivm->builder;
   LLVMValueRef mask = lp_build_const_int_vec(gallivm, dst_type, 0xff);
   unsigned chan;


   packed = LLVMBuildBitCast(builder, packed,
                             lp_build_int_vec_type(gallivm, dst_type), "");


   for (chan = 0; chan < 4; ++chan) {
#ifdef PIPE_ARCH_LITTLE_ENDIAN
      unsigned start = chan*8;
#else
      unsigned start = (3-chan)*8;
#endif
      unsigned stop = start + 8;
      LLVMValueRef input;

      input = packed;

      if (start)
         input = LLVMBuildLShr(builder, input,
                               lp_build_const_int_vec(gallivm, dst_type, start), "");

      if (stop < 32)
         input = LLVMBuildAnd(builder, input, mask, "");

      if (dst_type.floating)
         input = lp_build_unsigned_norm_to_float(gallivm, 8, dst_type, input);

      rgba[chan] = input;
   }
}
