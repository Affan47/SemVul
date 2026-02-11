getFirstChildWithType	(pANTLR3_BASE_TREE tree, ANTLR3_UINT32 type)
{
	ANTLR3_UINT32   i;
	ANTLR3_UINT32   cs;

	pANTLR3_BASE_TREE	t;
	if	(tree->children != NULL)
	{
		cs	= tree->children->size(tree->children);
		for	(i = 0; i < cs; i++)
		{
			t = (pANTLR3_BASE_TREE) (tree->children->get(tree->children, i));
			if  (tree->getType(t) == type)
			{
				return  (pANTLR3_BASE_TREE)t;
			}
		}
	}
	return  NULL;
}
