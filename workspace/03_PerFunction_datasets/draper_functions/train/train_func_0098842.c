parallelized_function_p (tree fn)
{
  if (!parallelized_functions || !DECL_ARTIFICIAL (fn))
    return false;

  return bitmap_bit_p (parallelized_functions, DECL_UID (fn));
}
