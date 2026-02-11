CheckNormals()
{
	int i;
	for (i=0;i<this->GetNumberOfCells();i++)
		this->VisitedPolygons->SetValue(i,0);


	for (i=0;i<this->GetNumberOfCells();i++)
	{
		if ((this->VisitedPolygons->GetValue(i)==0)&&(this->IsFaceActive(i)==1))
		{
			this->VisitedPolygons->SetValue(i,1);
			this->ConquerOrientationFromFace(i);
		}
	}
	this->OrientedSurface=true;
}
