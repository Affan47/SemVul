GetPlane(int i, vtkPlane *plane)
{
  double normal[3];
  double point[3];

  if ( i >= 0 && i < this->GetNumberOfPlanes() )
    {
    this->Normals->GetTuple(i,normal);
    this->Points->GetPoint(i,point);
    plane->SetNormal(normal);
    plane->SetOrigin(point);
    }
  else
    {
    plane = NULL;
    }
}
