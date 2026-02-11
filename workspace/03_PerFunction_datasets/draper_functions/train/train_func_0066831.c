SetImageDataPickInfo(const double x[3],
                                            const int extent[6])
{
  for (int j = 0; j < 3; j++)
    {
    double xj = x[j];
    if (xj < extent[2*j]) { xj = extent[2*j]; }
    if (xj > extent[2*j+1]) { xj = extent[2*j+1]; }

    this->CellIJK[j] = vtkMath::Floor(xj);
    this->PCoords[j] = xj - this->CellIJK[j];

    if (this->CellIJK[j] == extent[2*j+1] &&
        this->CellIJK[j] > extent[2*j])
      {
      this->CellIJK[j] -= 1;
      this->PCoords[j] = 1.0;
      }
    this->PointIJK[j] = this->CellIJK[j] + (this->PCoords[j] >= 0.5);
    }


  int ext[6];
  ext[0] = extent[0]; ext[1] = extent[1];
  ext[2] = extent[2]; ext[3] = extent[3];
  ext[4] = extent[4]; ext[5] = extent[5];

  this->PointId =
    vtkStructuredData::ComputePointIdForExtent(ext, this->PointIJK);

  this->CellId =
    vtkStructuredData::ComputeCellIdForExtent(ext, this->CellIJK);

  this->SubId = 0;
}
