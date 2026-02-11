gt_ggc_mx_VEC_constructor_elt_gc (void *x_p)
{
  struct VEC_constructor_elt_gc * const x = (struct VEC_constructor_elt_gc *)x_p;
  if (ggc_test_and_set_mark (x))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(((*x).base).num);
        for (i0 = 0; i0 != l0; i0++) {
          gt_ggc_m_9tree_node ((*x).base.vec[i0].index);
          gt_ggc_m_9tree_node ((*x).base.vec[i0].value);
        }
      }
    }
}
