free_rho_tree_memory(rhoTreeNode* rootNode)
{
  rhoTreeNode* child1;
  rhoTreeNode* child2;
  child1 = rootNode->child1;
  child2 = rootNode->child2;
  if(child1 != NULL)
    free_rho_tree_memory(child1);
  if(child2 != NULL)
    free_rho_tree_memory(child2);
  delete rootNode;
}
