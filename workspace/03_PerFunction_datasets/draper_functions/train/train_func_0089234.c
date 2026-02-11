DeleteTrianglesAreas()
{
	if (this->TrianglesAreas)
	{
		this->TrianglesAreas->Delete();
		this->TrianglesAreas=0;
	}
}
