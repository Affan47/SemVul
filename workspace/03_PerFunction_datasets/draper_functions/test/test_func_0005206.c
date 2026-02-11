RemoveTuple(double t)
{
  int i;
  if ( this->InterpolationType == INTERPOLATION_TYPE_LINEAR )
    {
    for (i=0; i<this->NumberOfComponents; i++)
      {
      this->Linear[i]->RemovePoint(t);
      }
    }

  else
    {
    for (i=0; i<this->NumberOfComponents; i++)
      {
      this->Spline[i]->RemovePoint(t);
      }
    }

  this->Modified();
}
