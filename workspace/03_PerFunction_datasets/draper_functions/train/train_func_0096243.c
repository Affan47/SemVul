applyTransitions ( const DlCompletionTreeArc* edge,
											const RAStateTransitions& RST,
											BipolarPointer C,
											const DepSet& dep, const char* reason )
{
	DlCompletionTree* node = edge->getArcEnd();

	if ( RST.isSingleton() )
		return addToDoEntry ( node, C+RST.getTransitionEnd(), dep, reason );

	RAStateTransitions::const_iterator q, end = RST.end();
	const TRole* R = edge->getRole();


	for ( q = RST.begin(); q != end; ++q )
	{
		incStat(nAutoTransLookups);
		if ( (*q)->applicable(R) )
			switchResult ( addToDoEntry ( node, C+(*q)->final(), dep, reason ) );
	}

	return false;
}
