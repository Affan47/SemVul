IsVertexManifold( const vtkIdType& iV )
{
	vtkIdType v1,v2;
	vtkIdType FirstEdge,FirstVertex;
	vtkIdType f1,f2,f3;
	vtkIdType *Edges,NumberOfRemainingEdges;

	this->GetVertexNeighbourEdges(iV,NumberOfRemainingEdges,Edges);


	if (NumberOfRemainingEdges<2)
		return (false);


	for (vtkIdType i=0;i<NumberOfRemainingEdges;i++)
	{
		if (!this->IsEdgeManifold(Edges[i]))
			return (false);
	}

	FirstEdge=this->GetFirstEdge(iV);
	this->GetEdgeVertices(FirstEdge,FirstVertex,v1);
	if (FirstVertex==iV)
		FirstVertex=v1;
	v1=FirstVertex;

	NumberOfRemainingEdges--;
	this->GetEdgeFaces(FirstEdge,f1,f2);


	v2=this->GetThirdPoint(f1,iV,FirstVertex);
	do
	{
		if (--NumberOfRemainingEdges==0)
			return (true);
		Conquer(f1,iV,v2,f3,v1);
		f1=f3;
		v2=v1;
	} while ((f1>=0)&&(v2!=FirstVertex));


	if ((f2<0)||(v2==FirstVertex))
		return (false);


	v1=FirstVertex;
	v2=this->GetThirdPoint(f2,iV,FirstVertex);
	do
	{
		if (--NumberOfRemainingEdges==0)
			return (true);
		Conquer(f2,iV,v2,f3,v1);
		f2=f3;
		v2=v1;

	} while ((f2>=0)&&(v2!=FirstVertex));

	return (false);
}
