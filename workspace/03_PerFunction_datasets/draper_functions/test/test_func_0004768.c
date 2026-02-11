createDifferentNeighbours ( const TRole* R, BipolarPointer C, const DepSet& dep,
													   unsigned int n, CTNominalLevel level )
{

	DlCompletionTreeArc* pA = NULL;
	CGraph.initIR();
	for ( unsigned int i = 0; i < n; ++i )
	{
		pA = createOneNeighbour ( R, dep, level );
		DlCompletionTree* child = pA->getArcEnd();


		CGraph.setCurIR ( child, dep );


		switchResult ( initNewNode ( child, dep, C ) );
		switchResult ( setupEdge ( pA, dep, redoForall ) );
	}
	CGraph.finiIR();


	return applyUniversalNR ( curNode, pA, dep, redoFunc|redoAtMost );
}
