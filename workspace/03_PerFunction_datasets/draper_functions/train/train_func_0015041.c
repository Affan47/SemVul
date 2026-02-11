delete_and_purge_tree(Node* node)
{
	if (node->left != m_pLeaf) {
		delete_and_purge_tree(node->left);
	}
	if (node->right != m_pLeaf) {
		delete_and_purge_tree(node->right);
	}
	if(node->item) {
		delete node->item;
	}
	delete node;
}
