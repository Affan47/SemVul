DetermineConstraintAxis(
  int constraint, double *x, double *startPickPoint)
{

  if ( ! this->Constrained )
    {
    return -1;
    }
  else if ( constraint >= 0 && constraint < 3 )
    {
    return constraint;
    }


  if ( ! x )
    {
    double p[3], d2, tol;
    this->CursorPicker->GetPickPosition(p);
    d2 = vtkMath::Distance2BetweenPoints(p,this->LastPickPosition);
    tol = this->HotSpotSize*this->InitialLength;
    if ( d2 > (tol*tol))
      {
      this->WaitingForMotion = 0;
      return this->CursorPicker->GetCellId();
      }
    else
      {
      this->WaitingForMotion = 1;
      this->WaitCount = 0;
      return -1;
      }
    }
  else if ( x)
    {
    this->WaitingForMotion = 0;
    double v[3];
    v[0] = fabs(x[0] - startPickPoint[0]);
    v[1] = fabs(x[1] - startPickPoint[1]);
    v[2] = fabs(x[2] - startPickPoint[2]);
    return ( v[0]>v[1] ? (v[0]>v[2]?0:2) : (v[1]>v[2]?1:2));
    }
  else
    {
    return -1;
    }
}
