AppendNode(Node* node) {


  ASSERT(node != NULL);
  if (exit()->IsExitNode()) return;
  if (exit()->IsBranchNode() && (node->IsJoinNode() || node->IsExitNode())) {
    AppendNode(new BlockNode());
  }
  exit()->AddSuccessor(node);
  node->AddPredecessor(exit());
  exit_ = node;
}
