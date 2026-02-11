removeNode(AVLTree * tree, TreeNode * node, void * data, void ** removedData)
{
	if(node == NULL)
		return NULL;

	int comparision = tree->compare(data, node->data);

	if(comparision > 0)
	{
		node->right = removeNode(tree, node->right, data, removedData);
	}

	if(comparision < 0)
	{
		node->left = removeNode(tree, node->left, data, removedData);
	}

	if(comparision == 0)
	{
		*removedData = node->data;

		if(node->left == NULL && node->right == NULL)
		{
			destroyNode(node);
			node = NULL;
			return node;
		}
		else if(node->left != NULL && node->right != NULL)
		{
			node->data = replaceWithData(node->left, data);
			node->left = removeNode(tree, node->left, data, removedData);
		}
		else if(node->left != NULL)
		{
			TreeNode * leftNode = node->left;
			*removedData = node->data;
			destroyNode(node);
			node = leftNode;
		}
		else
		{
			TreeNode * rightNode = node->right;
			*removedData = node->data;
			destroyNode(node);
			node = rightNode;
		}

	}

	updateHeight(node);

	node = balanceNode(node);

	return node;
}
