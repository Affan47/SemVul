createSNFLE ( unsigned int n, DLTree* R, DLTree* C )
{
	if ( C->Element() == BOTTOM )
	{
		deleteTree(R);
		deleteTree(C);
		return createTop();
	}
	if ( n == 0 )
		return createSNFForall ( R, createSNFNot(C) );
	if ( unlikely(isBotRole(R)) )
	{
		deleteTree(R);
		deleteTree(C);
		return createTop();
	}
	if ( unlikely(isTopRole(R)) && resolveRole(R)->isDataRole() )
	{
		deleteTree(R);
		return simplifyDataTopLE ( n, C );
	}
	return new DLTree ( TLexeme ( LE, n ), R, C );
}
