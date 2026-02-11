Contour(double value, vtkDataArray *cellScalars,
                               vtkIncrementalPointLocator *locator, vtkCellArray *verts,
                               vtkCellArray *lines, vtkCellArray *polys,
                               vtkPointData *inPd, vtkPointData *outPd,
                               vtkCellData *inCd, vtkIdType cellId,
                               vtkCellData *outCd)
{
  int i, numTris=this->Points->GetNumberOfPoints()-2;
  vtkDataArray *triScalars=cellScalars->NewInstance();
  triScalars->SetNumberOfComponents(cellScalars->GetNumberOfComponents());
  triScalars->SetNumberOfTuples(3);

  for ( i=0; i < numTris; i++)
    {
    this->Triangle->Points->SetPoint(0,this->Points->GetPoint(i));
    this->Triangle->Points->SetPoint(1,this->Points->GetPoint(i+1));
    this->Triangle->Points->SetPoint(2,this->Points->GetPoint(i+2));

    if ( outPd )
      {
      this->Triangle->PointIds->SetId(0,this->PointIds->GetId(i));
      this->Triangle->PointIds->SetId(1,this->PointIds->GetId(i+1));
      this->Triangle->PointIds->SetId(2,this->PointIds->GetId(i+2));
      }

    triScalars->SetTuple(0,cellScalars->GetTuple(i));
    triScalars->SetTuple(1,cellScalars->GetTuple(i+1));
    triScalars->SetTuple(2,cellScalars->GetTuple(i+2));

    this->Triangle->Contour(value, triScalars, locator, verts,
                           lines, polys, inPd, outPd, inCd, cellId, outCd);
    }
  triScalars->Delete();
}
