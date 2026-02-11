gt_ggc_mx_gimple_seq_node_d (void *x_p)
{
  struct gimple_seq_node_d * x = (struct gimple_seq_node_d *)x_p;
  struct gimple_seq_node_d * xlimit = x;
  while (ggc_test_and_set_mark (xlimit))
   xlimit = ((*xlimit).next);
  if (x != xlimit)
    for (;;)
      {
        struct gimple_seq_node_d * const xprev = ((*x).prev);
        if (xprev == NULL) break;
        x = xprev;
        (void) ggc_test_and_set_mark (xprev);
      }
  while (x != xlimit)
    {
      gt_ggc_m_18gimple_statement_d ((*x).stmt);
      gt_ggc_m_17gimple_seq_node_d ((*x).prev);
      gt_ggc_m_17gimple_seq_node_d ((*x).next);
      x = ((*x).next);
    }
}
