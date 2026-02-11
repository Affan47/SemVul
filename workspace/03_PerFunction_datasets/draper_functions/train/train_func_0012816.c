Clip(double value, vtkDataArray *cellScalars,
                      vtkIncrementalPointLocator *locator, vtkCellArray *tris,
                      vtkPointData *inPD, vtkPointData *outPD,
                      vtkCellData *inCD, vtkIdType cellId, vtkCellData *outCD,
                      int insideOut)
{
  int i, success;
  double *bounds, d;
  int p1, p2, p3;

  this->TriScalars->SetNumberOfTuples(3);

  bounds = this->GetBounds();
  d = sqrt((bounds[1]-bounds[0])*(bounds[1]-bounds[0]) +
           (bounds[3]-bounds[2])*(bounds[3]-bounds[2]) +
           (bounds[5]-bounds[4])*(bounds[5]-bounds[4]));
  this->Tolerance = VTK_POLYGON_TOLERANCE * d;

  this->SuccessfulTriangulation = 1;
  this->ComputeNormal(this->Points, this->Normal);

  this->Tris->Reset();

  success = this->EarCutTriangulation();

  if ( success )
    {
    for (i=0; i<this->Tris->GetNumberOfIds(); i += 3)
      {
      p1 = this->Tris->GetId(i);
      p2 = this->Tris->GetId(i+1);
      p3 = this->Tris->GetId(i+2);

      this->Triangle->Points->SetPoint(0,this->Points->GetPoint(p1));
      this->Triangle->Points->SetPoint(1,this->Points->GetPoint(p2));
      this->Triangle->Points->SetPoint(2,this->Points->GetPoint(p3));

      this->Triangle->PointIds->SetId(0,this->PointIds->GetId(p1));
      this->Triangle->PointIds->SetId(1,this->PointIds->GetId(p2));
      this->Triangle->PointIds->SetId(2,this->PointIds->GetId(p3));

      this->TriScalars->SetTuple(0,cellScalars->GetTuple(p1));
      this->TriScalars->SetTuple(1,cellScalars->GetTuple(p2));
      this->TriScalars->SetTuple(2,cellScalars->GetTuple(p3));

      this->Triangle->Clip(value, this->TriScalars, locator, tris,
                          inPD, outPD, inCD, cellId, outCD, insideOut);
      }
    }
}
