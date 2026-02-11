PrintAsCSV(ostream &os)
{
  vtkDataArray *scalars;
  vtkDataSet *ds;
  vtkCollectionSimpleIterator dsit;
  double s;
  int dsNum,component;
  for ( dsNum=0, this->InputList->InitTraversal(dsit);
    (ds = this->InputList->GetNextDataSet(dsit)); dsNum++ )
    {
    vtkIdType numPts = ds->GetNumberOfPoints();
    scalars = ds->GetPointData()->GetScalars(this->SelectedInputScalars[dsNum]);
    os << this->SelectedInputScalars[dsNum] << ",";

    component = this->SelectedInputScalarsComponent->GetValue(dsNum);
    for ( vtkIdType ptId=0; ptId < numPts; ptId++ )
      {
      s = scalars->GetComponent(ptId, component);
      if( ptId == 0 )
        {
        os << s;
        }
      else
        {
        os << "," << s;
        }
      }
    os << endl;

    if (dsNum == this->InputList->GetNumberOfItems()-1)
      {
      os << "X or T,";
      for ( vtkIdType ptId=0; ptId < numPts; ptId++ )
        {
        double *x = ds->GetPoint(ptId);
        if( ptId == 0 )
          {
          os << x[0];
          }
        else
          {
          os << "," << x[0];
          }
        }
      os << endl;
      }

    }
}
