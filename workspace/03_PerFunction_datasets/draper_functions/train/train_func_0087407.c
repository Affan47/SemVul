ComputeScalarRange()
{
  if ( this->GetMTime() > this->ScalarRangeComputeTime )
    {
    vtkDataArray *ptScalars, *cellScalars;
    ptScalars = this->PointData->GetScalars();
    cellScalars = this->CellData->GetScalars();

    if ( ptScalars && cellScalars)
      {
      double r1[2], r2[2];
      ptScalars->GetRange(r1,0);
      cellScalars->GetRange(r2,0);
      this->ScalarRange[0] = (r1[0] < r2[0] ? r1[0] : r2[0]);
      this->ScalarRange[1] = (r1[1] > r2[1] ? r1[1] : r2[1]);
      }
    else if ( ptScalars )
      {
      ptScalars->GetRange(this->ScalarRange,0);
      }
    else if ( cellScalars )
      {
      cellScalars->GetRange(this->ScalarRange,0);
      }
    else
      {
      this->ScalarRange[0] = 0.0;
      this->ScalarRange[1] = 1.0;
      }
    this->ScalarRangeComputeTime.Modified();
    }
}
