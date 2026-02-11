aarch64_simd_dup_constant (rtx vals)
{
  enum machine_mode mode = GET_MODE (vals);
  enum machine_mode inner_mode = GET_MODE_INNER (mode);
  int n_elts = GET_MODE_NUNITS (mode);
  bool all_same = true;
  rtx x;
  int i;

  if (GET_CODE (vals) != CONST_VECTOR)
    return NULL_RTX;

  for (i = 1; i < n_elts; ++i)
    {
      x = CONST_VECTOR_ELT (vals, i);
      if (!rtx_equal_p (x, CONST_VECTOR_ELT (vals, 0)))
	all_same = false;
    }

  if (!all_same)
    return NULL_RTX;


  x = copy_to_mode_reg (inner_mode, CONST_VECTOR_ELT (vals, 0));
  return gen_rtx_VEC_DUPLICATE (mode, x);
}
