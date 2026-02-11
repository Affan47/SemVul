gt_pch_p_16machine_function (ATTRIBUTE_UNUSED void *this_obj,
	void *x_p,
	ATTRIBUTE_UNUSED gt_pointer_operator op,
	ATTRIBUTE_UNUSED void *cookie)
{
  struct machine_function * x ATTRIBUTE_UNUSED = (struct machine_function *)x_p;
  if ((void *)(x) == this_obj)
    op (&((*x).eh_epilogue_sp_ofs), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).pic_reg), cookie);
  {
    size_t i0;
    size_t l0 = (size_t)(14);
    for (i0 = 0; i0 != l0; i0++) {
      if ((void *)(x) == this_obj)
        op (&((*x).call_via[i0]), cookie);
    }
  }
  if ((void *)(x) == this_obj)
    op (&((*x).thumb1_cc_insn), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).thumb1_cc_op0), cookie);
  if ((void *)(x) == this_obj)
    op (&((*x).thumb1_cc_op1), cookie);
}
