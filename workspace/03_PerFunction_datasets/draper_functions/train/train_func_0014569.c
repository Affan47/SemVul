OptimizeSoon(JSFunction* function) {
  if (!IsOptimizable(function)) return;
  PendingListNode* node = new PendingListNode(function);
  node->set_next(optimize_soon_list);
  optimize_soon_list = node;
}
