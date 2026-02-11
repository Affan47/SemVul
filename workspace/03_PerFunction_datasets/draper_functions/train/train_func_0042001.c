EvaluateSecondDerivative(double t)
{
  int index;
  double *intervals;
  double *coefficients;

  if (this->ComputeTime < this->GetMTime())
    {
    this->Compute();
    }

  int size = this->PiecewiseFunction->GetSize();
  if (size < 2)
    {
    return 0.0;
    }

  intervals = this->Intervals;
  coefficients = this->Coefficients;

  if (this->Closed)
    {
    size = size + 1;
    }

  if (t < intervals[0])
    {
    t = intervals[0];
    }
  if (t > intervals[size - 1])
    {
    t = intervals[size - 1];
    }

  index = this->FindIndex(size,t);

  t = (t - intervals[index]);

  return 6 * t * *(coefficients + index * 4 + 3) +
             2 * *(coefficients + index * 4 + 2);
}
