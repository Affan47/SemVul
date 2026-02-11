OffsetPoint(vtkIdType ptId, vtkPoints *inPts, double n[3],
                                vtkPoints *newPts, double offset,
                                double *range, double v)
{
  double x[3], xNew[3];
  int i;
  double median = (range[0] + range[1])/2.0;
  double denom = range[1] - range[0];

  inPts->GetPoint(ptId, x);
  for (i=0; i<3; i++)
    {
    xNew[i] = x[i] + n[i] * (offset + ((v - median)/denom)*this->Height);
    }

  return newPts->InsertNextPoint(xNew);
}
