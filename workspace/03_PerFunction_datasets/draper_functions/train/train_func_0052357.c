processOrEntry ( void )
{

	const BCOr* bcOr = static_cast<BCOr*>(bContext);
	BCOr::or_iterator p = bcOr->orBeg(), p_end = bcOr->orCur();
	ConceptWDep C = *p_end;
	const char* reason = NULL;
	DepSet dep;

	if ( bcOr->isLastOrEntry() )
	{

		prepareBranchDep();
		dep = getBranchDep();

		determiniseBranchingOp();
		reason = "bcp";
	}
	else
	{

		save();

		dep = getCurDepSet();
		incStat(nOrBrCalls);
	}


	if ( useSemanticBranching() )
		for ( ; p < p_end; ++p )
			if ( addToDoEntry ( curNode, ConceptWDep(inverse(*p),dep), "sb" ) )
				fpp_unreachable();


	return
#	ifdef RKG_USE_DYNAMIC_BACKJUMPING
		addToDoEntry ( curNode, ConceptWDep(C,dep), reason );
#	else
		insertToDoEntry ( curNode, ConceptWDep(C,dep), DLHeap[C].Type(), reason );
#	endif
}
