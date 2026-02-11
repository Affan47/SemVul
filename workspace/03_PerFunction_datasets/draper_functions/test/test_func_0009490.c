lp_llvm_sampler_member(const struct lp_sampler_dynamic_state *base,
                       struct gallivm_state *gallivm,
                       unsigned sampler_unit,
                       unsigned member_index,
                       const char *member_name,
                       boolean emit_load)
{
   struct llvmpipe_sampler_dynamic_state *state =
      (struct llvmpipe_sampler_dynamic_state *)base;
   LLVMBuilderRef builder = gallivm->builder;
   LLVMValueRef indices[4];
   LLVMValueRef ptr;
   LLVMValueRef res;

   assert(sampler_unit < PIPE_MAX_SAMPLERS);


   indices[0] = lp_build_const_int32(gallivm, 0);

   indices[1] = lp_build_const_int32(gallivm, LP_JIT_CTX_SAMPLERS);

   indices[2] = lp_build_const_int32(gallivm, sampler_unit);

   indices[3] = lp_build_const_int32(gallivm, member_index);

   ptr = LLVMBuildGEP(builder, state->context_ptr, indices, Elements(indices), "");

   if (emit_load)
      res = LLVMBuildLoad(builder, ptr, "");
   else
      res = ptr;

   lp_build_name(res, "context.sampler%u.%s", sampler_unit, member_name);

   return res;
}
