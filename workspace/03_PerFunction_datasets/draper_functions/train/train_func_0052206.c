C_2_times(C_word **ptr, C_word x, C_word y)
{
  C_word iresult;

  if(x & C_FIXNUM_BIT) {
    if(y & C_FIXNUM_BIT) {
      iresult = C_i_o_fixnum_times(x, y);

      if(iresult == C_SCHEME_FALSE)
	return C_flonum(ptr, (double)C_unfix(x) * (double)C_unfix(y));
      else return iresult;
    }
    else if(!C_immediatep(y) && C_block_header(y) == C_FLONUM_TAG)
      return C_flonum(ptr, (double)C_unfix(x) * C_flonum_magnitude(y));
    else barf(C_BAD_ARGUMENT_TYPE_ERROR, "*", y);
  }
  else if(!C_immediatep(x) && C_block_header(x) == C_FLONUM_TAG) {
    if(y & C_FIXNUM_BIT)
      return C_flonum(ptr, C_flonum_magnitude(x) * (double)C_unfix(y));
    else if(!C_immediatep(y) && C_block_header(y) == C_FLONUM_TAG)
      return C_flonum(ptr, C_flonum_magnitude(x) * C_flonum_magnitude(y));
    else barf(C_BAD_ARGUMENT_TYPE_ERROR, "*", y);
  }
  else barf(C_BAD_ARGUMENT_TYPE_ERROR, "*", x);
}
