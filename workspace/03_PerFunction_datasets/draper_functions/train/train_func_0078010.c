CleanVertex(vtkIdType Vertex)
{
	if (this->CleanVertices==0)
		return;
	if (this->GetValence(Vertex)==0)
		this->DeleteVertex(Vertex);
}
