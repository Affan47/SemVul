GetMinimumT()
{
  if ( this->Spline )
    {
    double range[2];
    this->Spline[0]->GetParametricRange(range);
    return range[0];
    }
  else if ( this->Linear )
    {
    return this->Linear[0]->GetRange()[0];
    }
  else
    {
    return 0.0;
    }
}
