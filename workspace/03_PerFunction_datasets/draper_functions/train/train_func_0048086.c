getNodedEdges()
{
	EdgeSetIntersector *esi=new SimpleMCSweepLineIntersector();
	SegmentIntersector *si=new SegmentIntersector(li,true,false);
	esi->computeIntersections(inputEdges,si,true);

	vector<Edge*> *splitEdges=new vector<Edge*>();
	for(int i=0;i<(int)inputEdges->size();i++) {
		Edge* e=(*inputEdges)[i];
		e->getEdgeIntersectionList().addSplitEdges(splitEdges);
	}
	return splitEdges;
}

}
