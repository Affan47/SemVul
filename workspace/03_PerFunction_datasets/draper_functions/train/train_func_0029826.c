addSubsumeAxiom ( DLTree* sub, DLTree* sup )
{

	if ( equalTrees ( sub, sup ) )
	{
		deleteTree(sub);
		deleteTree(sup);
		return;
	}


	if ( isCN(sup) )
		if ( applyAxiomCToCN ( sub, sup ) )
			return;


	if ( isCN(sub) )
		if ( applyAxiomCNToC ( sub, sup ) )
			return;


	if ( axiomToRangeDomain ( sub, sup ) )
		;
	else
		processGCI ( sub, sup );
}
