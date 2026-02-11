UpdateReachability( CT_vertex *vertexFrom, CT_vertex *vertexTo )
{
	bool addedNewReachingVertex = false;


	this->num_update_reachabilities++;


	vertexSet_it iterTo = vertexTo->reachingVertices.begin();
	vertexSet_it iterToPrev = iterTo;
	vertexSet_it iterToEnd = vertexTo->reachingVertices.end();
	for (vertexSet_it iterFrom = vertexFrom->reachingVertices.begin();
		 iterFrom != vertexFrom->reachingVertices.end(); iterFrom++) {
		while ((*iterTo < *iterFrom) && (iterTo != iterToEnd)) {
			iterToPrev = iterTo;
			iterTo++;
		}
		if ((*iterFrom == *iterTo) && (iterTo != iterToEnd)) {

			continue;
		}
		if (this->pt.compareFormulaSize( vertexTo->subformula,
										 (*iterFrom)->subformula))
			continue;
		vertexTo->reachingVertices.insert (iterToPrev, *iterFrom);
		addedNewReachingVertex = true;
	}


	if ((vertexTo->subformula->type == PT_VAR) ) {

		PT_node *bindingSubformula = this->pt.getBoundFormula (vertexTo->subformula);

		bool gfpLoopFound = false;
		for (vertexSet_it iter = vertexTo->reachingVertices.begin();
			 iter != vertexTo->reachingVertices.end(); iter++) {
			CT_vertex *vertexCurr = *iter;
			if ((vertexCurr->state == vertexTo->state)
				&& (vertexCurr->subformula == bindingSubformula)) {
				gfpLoopFound = true;
				break;
			}
		}
		if (gfpLoopFound) {
			this->satVertices.insert (vertexTo);
		}
	}


	if (addedNewReachingVertex) {
		for (vertexSet_it iter = vertexTo->succVertices.begin();
			 iter != vertexTo->succVertices.end(); iter++) {
			this->UpdateReachability (vertexTo,*iter);
		}
	}

	return addedNewReachingVertex;
}
