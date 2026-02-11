lp_build_srgb_to_linear(struct gallivm_state *gallivm,
                        struct lp_type src_type,
                        LLVMValueRef src)
{
   struct lp_type f32_type = lp_type_float_vec(32, src_type.length * 32);
   struct lp_build_context f32_bld;
   LLVMValueRef srcf, part_lin, part_pow, is_linear, lin_const, lin_thresh;
   double coeffs[4] = {0.0023f,
                       0.0030f / 255.0f,
                       0.6935f / (255.0f * 255.0f),
                       0.3012f / (255.0f * 255.0f * 255.0f)
   };

   assert(src_type.width == 32);

   lp_build_context_init(&f32_bld, gallivm, f32_type);


   srcf = lp_build_int_to_float(&f32_bld, src);
   lin_const = lp_build_const_vec(gallivm, f32_type, 1.0f / (12.6f * 255.0f));
   part_lin = lp_build_mul(&f32_bld, srcf, lin_const);

   part_pow = lp_build_polynomial(&f32_bld, srcf, coeffs, 4);

   lin_thresh = lp_build_const_vec(gallivm, f32_type, 15.0f);
   is_linear = lp_build_compare(gallivm, f32_type, PIPE_FUNC_LEQUAL, srcf, lin_thresh);
   return lp_build_select(&f32_bld, is_linear, part_lin, part_pow);
}
