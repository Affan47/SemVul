find_predecessors (sbitmap preds, ddg_ptr g, sbitmap ops)
{
  unsigned int i = 0;
  sbitmap_iterator sbi;

  EXECUTE_IF_SET_IN_BITMAP (ops, 0, i, sbi)
    {
      const sbitmap node_preds = NODE_PREDECESSORS (&g->nodes[i]);
      bitmap_ior (preds, preds, node_preds);
    };


  bitmap_and_compl (preds, preds, ops);
}
