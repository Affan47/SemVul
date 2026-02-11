gimple_build_call_internal_vec (enum internal_fn fn, VEC(tree, heap) *args)
{
  unsigned i, nargs;
  gimple call;

  nargs = VEC_length (tree, args);
  call = gimple_build_call_internal_1 (fn, nargs);
  for (i = 0; i < nargs; i++)
    gimple_call_set_arg (call, i, VEC_index (tree, args, i));

  return call;
}
