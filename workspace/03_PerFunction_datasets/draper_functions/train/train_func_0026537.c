Node_index (Node_T node, int *index) {
  if (node != NULL) {
    node->index = (*index)++;
    Node_index(node->left,&(*index));
    Node_index(node->right,&(*index));
  }
  return;
}
