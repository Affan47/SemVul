sort_scc (VEC (tree, heap) *scc)
{
  VEC_qsort (tree, scc, compare_ops);
}
