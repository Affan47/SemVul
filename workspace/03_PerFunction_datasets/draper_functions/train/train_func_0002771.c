affine_function_constant_p (affine_fn fn)
{
  unsigned i;
  tree coef;

  for (i = 1; VEC_iterate (tree, fn, i, coef); i++)
    if (!integer_zerop (coef))
      return false;

  return true;
}
