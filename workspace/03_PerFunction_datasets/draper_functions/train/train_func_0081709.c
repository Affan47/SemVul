setContains(Set *set, int val)
{
	SetNode *node;
	int n = setHash(val);

	for (node = set->node[n];node != NULL;node = node->next)
	{
		if (node->val == val) { return 1; }
	}

	return 0;
}
