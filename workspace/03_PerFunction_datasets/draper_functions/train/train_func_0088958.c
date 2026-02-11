InverseTransformPoints(vtkPoints2D *inPts, vtkPoints2D *outPts)
{
  vtkIdType n = inPts->GetNumberOfPoints();
  outPts->SetNumberOfPoints(n);
  if (this->Matrix->GetMTime() > this->InverseMatrix->GetMTime())
    {
    this->Matrix->Invert(this->Matrix, this->InverseMatrix);
    }
  double *M = this->InverseMatrix->GetData();
  double point[2];

  for (int i = 0; i < n; ++i)
    {
    inPts->GetPoint(i,point);
    vtkHomogeneousTransformPoint2D(M,point,point);
    outPts->SetPoint(i, point);
    }
}
