getStateTrajectoryBetweenVertices (CT_vertex *vertexInitial, CT_vertex *vertexFinal )
{

	vertexList *solutionVertexList = NULL;
	vertexListSet vertexListsCurr;

	vertexList *vertexListFinal = new vertexList;
	vertexListFinal->push_back (vertexFinal);

	vertexListsCurr.insert (vertexListFinal);


	vertexSet verticesProcessed;
	verticesProcessed.clear ();

	verticesProcessed.insert (vertexFinal);

	bool vertex_exists = true;
	while (vertex_exists) {

		vertex_exists = false;
		bool solutionFound = false;
		vertexListSet vertexListsNext;
		for (vertexListSet_it iter = vertexListsCurr.begin(); iter != vertexListsCurr.end(); iter++) {
			vertexList *vertexListThis = *iter;
			CT_vertex *vertexLastInList = *(vertexListThis->rbegin());
			if ( vertexLastInList == vertexInitial) {

				solutionVertexList = vertexListThis;
				solutionFound = true;
				break;
			}
			for (vertexSet_it iter2 = vertexLastInList->predVertices.begin();
				 iter2 != vertexLastInList->predVertices.end(); iter2++) {
				CT_vertex *vertexPred = *iter2;
				if (verticesProcessed.find (vertexPred) == verticesProcessed.end() ) {
					vertexList *vertexListNew = new vertexList;
					for (vertexList_it iter3 = vertexListThis->begin();
						 iter3 != vertexListThis->end(); iter3++) {
						vertexListNew->push_back (*iter3);
					}
					vertexListNew->push_back (vertexPred);
					vertexListsNext.insert (vertexListNew);
					verticesProcessed.insert (vertexPred);
					vertex_exists = true;
				}
			}
		}
		if (!solutionFound) {
			for (vertexListSet_it iter = vertexListsCurr.begin();
				 iter != vertexListsCurr.end(); iter++) {
				vertexList *vertexListThis = *iter;
				delete vertexListThis;
			}
			vertexListsCurr.clear();
			for (vertexListSet_it iter = vertexListsNext.begin();
				 iter != vertexListsNext.end(); iter++) {
				vertexListsCurr.insert(*iter);
			}
		}
	}


	stateList trajectory;
	trajectory.clear();
	MS_state *stateLastInTrajectory = NULL;
	for (vertexList_rit iter = solutionVertexList->rbegin();
		 iter != solutionVertexList->rend(); iter++) {
		CT_vertex *vertexThis = *iter;
		MS_state *stateThis = vertexThis->state;
		if (stateThis != stateLastInTrajectory) {
			trajectory.push_back (stateThis);
			stateLastInTrajectory = stateThis;
		}
	}

	return trajectory;

}
