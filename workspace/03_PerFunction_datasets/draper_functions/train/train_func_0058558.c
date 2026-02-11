C_u_i_positivep(C_word x)
{
  if(x & C_FIXNUM_BIT) return C_mk_bool(C_unfix(x) > 0);

  return C_mk_bool(C_flonum_magnitude(x) > 0.0);
}
