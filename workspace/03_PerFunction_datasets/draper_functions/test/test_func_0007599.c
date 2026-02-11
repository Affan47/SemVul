addEdges(const TPolyhedronFace &f)	{
	TPolyhedronEdge e;
	vector<uint32_t>::const_iterator it=f.vertices.begin();
	e.v1=*it;
	++it;
	while (it!=f.vertices.end())	{
		e.v2=*it;
		if (find(mEdges.begin(),mEdges.end(),e)==mEdges.end()) mEdges.push_back(e);
		e.v1=e.v2;
		++it;
	}
	e.v2=*(f.vertices.begin());
	if (find(mEdges.begin(),mEdges.end(),e)==mEdges.end()) mEdges.push_back(e);
}
