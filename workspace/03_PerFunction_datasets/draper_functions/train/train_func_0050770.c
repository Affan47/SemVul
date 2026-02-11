gt_pch_p_22VEC_ipa_jump_func_t_gc (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct VEC_ipa_jump_func_t_gc * const x ATTRIBUTE_UNUSED = (struct VEC_ipa_jump_func_t_gc *)x_p;
  {
    size_t i0;
    size_t l0 = (size_t)(((*x).base).prefix.num);
    for (i0 = 0; i0 != l0; i0++) {
      switch (((*x).base.vec[i0]).type)
        {
        case IPA_JF_KNOWN_TYPE:
          if ((void *)(x) == this_obj)
            op (&((*x).base.vec[i0].value.known_type.base_type), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).base.vec[i0].value.known_type.component_type), cookie);
          break;
        case IPA_JF_CONST:
          if ((void *)(x) == this_obj)
            op (&((*x).base.vec[i0].value.constant), cookie);
          break;
        case IPA_JF_CONST_MEMBER_PTR:
          if ((void *)(x) == this_obj)
            op (&((*x).base.vec[i0].value.member_cst.pfn), cookie);
          if ((void *)(x) == this_obj)
            op (&((*x).base.vec[i0].value.member_cst.delta), cookie);
          break;
        case IPA_JF_PASS_THROUGH:
          if ((void *)(x) == this_obj)
            op (&((*x).base.vec[i0].value.pass_through.operand), cookie);
          break;
        case IPA_JF_ANCESTOR:
          if ((void *)(x) == this_obj)
            op (&((*x).base.vec[i0].value.ancestor.type), cookie);
          break;
        default:
          break;
        }
    }
  }
}
