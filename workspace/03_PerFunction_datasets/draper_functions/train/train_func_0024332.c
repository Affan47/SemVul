Translate(double *p1, double *p2)
{

  double v[3], pos[3];
  v[0] = p2[0] - p1[0];
  v[1] = p2[1] - p1[1];
  v[2] = p2[2] - p1[2];

  this->GetWorldPosition( pos );
  double newFocus[3];
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
    newFocus[i] = pos[i] + v[i];
    }

  this->SetWorldPosition(newFocus);
}
