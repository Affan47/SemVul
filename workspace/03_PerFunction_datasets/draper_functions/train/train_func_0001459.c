DetermineConstraintAxis(int constraint, double *x)
{

  if ( ! this->Constrained )
    {
    return -1;
    }
  else if ( constraint >= 0 && constraint < 3 )
    {
    return constraint;
    }


  if ( ! this->WaitingForMotion )
    {
    double p[3], d2, tol;
    this->CursorPicker->GetPickPosition(p);
    d2 = vtkMath::Distance2BetweenPoints(p,this->StartEventPosition);
    tol = this->HotSpotSize*this->InitialLength;
    if ( d2 > (tol*tol) )
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
  else if ( this->WaitingForMotion && x )
    {
    double v[3];
    this->WaitingForMotion = 0;
    v[0] = fabs(x[0] - this->StartEventPosition[0]);
    v[1] = fabs(x[1] - this->StartEventPosition[1]);
    v[2] = fabs(x[2] - this->StartEventPosition[2]);
    return ( v[0]>v[1] ? (v[0]>v[2]?0:2) : (v[1]>v[2]?1:2));
    }
  else
    {
    return -1;
    }
}
