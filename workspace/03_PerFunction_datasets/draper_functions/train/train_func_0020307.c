isTSuccLabelled ( const TRole* R, BipolarPointer C ) const
{
	if ( isLabelledBy(C) )
		return this;

	if ( isNominalNode() )
		return NULL;


	const DlCompletionTree* ret = NULL;
	for ( const_edge_iterator p = begin(), p_end = end(); p < p_end; ++p )
		if ( (*p)->isSuccEdge() &&
			 (*p)->isNeighbour(R) &&
			 !(*p)->isReflexiveEdge() &&
			 (ret = (*p)->getArcEnd()->isTSuccLabelled(R,C)) != NULL )
			return ret;


	return NULL;
}
