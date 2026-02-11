C_i_zerop(C_word x)
{
  if(x & C_FIXNUM_BIT) return C_mk_bool(x == C_fix(0));

  if(C_immediatep(x) || C_block_header(x) != C_FLONUM_TAG)
    barf(C_BAD_ARGUMENT_TYPE_ERROR, "zero?", x);

  return C_mk_bool(C_flonum_magnitude(x) == 0.0);
}
