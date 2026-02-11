commonTacticBodySomeUniv ( const DLVertex& cur )
{

	if ( isCurNodeBlocked() )
		return false;

	incStat(nSomeCalls);

	BipolarPointer C = inverse(cur.getC());

	for ( DlCompletionGraph::iterator p = CGraph.begin(), p_end = CGraph.end(); p != p_end; ++p )
		if ( isObjectNodeUnblocked(*p) && (*p)->label().contains(C) )
			return false;

	return initNewNode ( CGraph.getNewNode(), curConcept.getDep(), C );
}
