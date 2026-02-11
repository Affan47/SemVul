addSplitEdges(vector<Edge*> *edgeList)
{


	addEndpoints();

	EdgeIntersectionList::iterator it=nodeMap.begin();


	EdgeIntersection *eiPrev=*it;
	++it;

	while (it!=nodeMap.end()) {
		EdgeIntersection *ei=*it;
		Edge *newEdge=createSplitEdge(eiPrev,ei);
		edgeList->push_back(newEdge);
		eiPrev=ei;
		it++;
	}
}
