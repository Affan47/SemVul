setupEdge ( DlCompletionTreeArc* pA, const DepSet& dep, unsigned int flags )
{
	DlCompletionTree* child = pA->getArcEnd();
	DlCompletionTree* from = pA->getReverse()->getArcEnd();


	switchResult ( initHeadOfNewEdge ( from, pA->getRole(), dep, "RD" ) );
	switchResult ( initHeadOfNewEdge ( child, pA->getReverse()->getRole(), dep, "RR" ) );


	switchResult ( applyUniversalNR ( from, pA, dep, flags ) );


	if ( pA->isPredEdge() || child->isNominalNode() || child == from )
		switchResult ( applyUniversalNR ( child, pA->getReverse(), dep, flags ) );
	else
	{
		if ( child->isDataNode() )
		{
			checkDataNode = true;
			switchResult ( checkDataClash(child) );
		}
		else
			switchResult ( usageByState(tryCacheNode(child)) );
	}


	return false;
}
