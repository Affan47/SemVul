destroySubTree(TreeNode * node, void (*destroyData)(void * data))
{
	if(node == NULL)
		return;

	destroySubTree(node->left, destroyData);
	destroySubTree(node->right, destroyData);

	if(destroyData != NULL)
		destroyData(node->data);

	destroyNode(node);
}
