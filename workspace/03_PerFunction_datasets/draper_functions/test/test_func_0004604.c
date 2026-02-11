C_i_exactp(C_word x)
{
  if(x & C_FIXNUM_BIT) return C_SCHEME_TRUE;

  if(C_immediatep(x) || C_block_header(x) != C_FLONUM_TAG)
    barf(C_BAD_ARGUMENT_TYPE_ERROR, "exact?", x);

  return C_SCHEME_FALSE;
}
