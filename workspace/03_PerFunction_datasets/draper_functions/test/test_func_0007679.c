Translate(double *p1, double *p2)
{

  double v[3];
  v[0] = p2[0] - p1[0];
  v[1] = p2[1] - p1[1];
  v[2] = p2[2] - p1[2];

  double *bounds = this->Cursor3D->GetModelBounds();
  double *pos = this->Cursor3D->GetFocalPoint();
  double newBounds[6], newFocus[3];
  int i;

  if ( this->ConstraintAxis >= 0 )
    {
    for (i=0; i<3; i++)
      {
      if ( i != this->ConstraintAxis )
        {
        v[i] = 0.0;
        }
      }
    }

  for (i=0; i<3; i++)
    {
    newBounds[2*i] = bounds[2*i] + v[i];
    newBounds[2*i+1] = bounds[2*i+1] + v[i];
    newFocus[i] = pos[i] + v[i];
    }

  this->Cursor3D->SetModelBounds(newBounds);
  this->Cursor3D->SetFocalPoint(newFocus);
}
