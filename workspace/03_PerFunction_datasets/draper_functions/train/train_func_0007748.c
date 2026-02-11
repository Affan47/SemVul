lp_build_blend_func(struct lp_build_context *bld,
                    unsigned func,
                    LLVMValueRef term1,
                    LLVMValueRef term2)
{
   switch (func) {
   case PIPE_BLEND_ADD:
      return lp_build_add(bld, term1, term2);
   case PIPE_BLEND_SUBTRACT:
      return lp_build_sub(bld, term1, term2);
   case PIPE_BLEND_REVERSE_SUBTRACT:
      return lp_build_sub(bld, term2, term1);
   case PIPE_BLEND_MIN:
      return lp_build_min(bld, term1, term2);
   case PIPE_BLEND_MAX:
      return lp_build_max(bld, term1, term2);
   default:
      assert(0);
      return bld->zero;
   }
}
