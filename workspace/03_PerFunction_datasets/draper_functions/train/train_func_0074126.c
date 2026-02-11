C_i_inexact_to_exact(C_word n)
{
  C_word r;

  if(n & C_FIXNUM_BIT) return n;
  else if(C_immediatep(n) || C_block_header(n) != C_FLONUM_TAG)
    barf(C_BAD_ARGUMENT_TYPE_ERROR, "inexact->exact", n);

  r = maybe_inexact_to_exact(n);
  if (r != C_SCHEME_FALSE) return r;

  barf(C_CANT_REPRESENT_INEXACT_ERROR, "inexact->exact", n);
  return 0;
}
