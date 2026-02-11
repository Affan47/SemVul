FindParameter(const char* name) const
{
	for (const FCDENode** itN = children.begin(); itN != children.end(); ++itN)
	{
		const FCDENode* node = (*itN);
		if (IsEquivalent(node->GetName(), name)) return node;
	}
	return NULL;
}
