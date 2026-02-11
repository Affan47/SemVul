isNNApplicable ( const TRole* r, BipolarPointer C, BipolarPointer stopper ) const
{

	if ( !curNode->isNominalNode() )
		return false;


	if ( isUsed(stopper) && curNode->isLabelledBy(stopper) )
		return false;


	DlCompletionTree::const_edge_iterator p, p_end = curNode->end(), q;
	for ( p = curNode->begin(); p != p_end; ++p )
	{
		const DlCompletionTree* suspect = (*p)->getArcEnd();


		if ( (*p)->isPredEdge() && suspect->isBlockableNode() && (*p)->isNeighbour(r) && suspect->isLabelledBy(C) )
		{
			if ( LLM.isWritable(llGTA) )
				LL << " NN(" << suspect->getId() << ")";

			return true;
		}
	}


	return false;
}
