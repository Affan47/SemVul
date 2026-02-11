X509_policy_tree_get0_level(const X509_POLICY_TREE *tree, int i)
	{
	if (!tree || (i < 0) || (i >= tree->nlevel))
		return NULL;
	return tree->levels + i;
	}
