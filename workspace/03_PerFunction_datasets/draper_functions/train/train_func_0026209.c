newFromTree(pANTLR3_ARBORETUM factory, pANTLR3_COMMON_TREE tree)
{
	pANTLR3_BASE_TREE	newTree;

	newTree = factory->newTree(factory);

	if	(newTree == NULL)
	{
		return	NULL;
	}


	((pANTLR3_COMMON_TREE)(newTree->super))->token   = tree->token;
	newTree->u		    = tree->baseTree.u;

	return  newTree;
}
