updateHeight(TreeNode * node)
{
	if(nodeHeight(node->left) > nodeHeight(node->right))
		node->height = nodeHeight(node->left) + 1;
	else
		node->height = nodeHeight(node->right) + 1;
}
