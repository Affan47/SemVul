common_affine_function (conflict_function *cf)
{
  unsigned i;
  affine_fn comm;

  if (!CF_NONTRIVIAL_P (cf))
    return affine_fn();

  comm = cf->fns[0];

  for (i = 1; i < cf->n; i++)
    if (!affine_function_equal_p (comm, cf->fns[i]))
      return affine_fn();

  return comm;
}
