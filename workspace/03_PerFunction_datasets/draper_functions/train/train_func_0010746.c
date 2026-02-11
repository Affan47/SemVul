ResizePointList(vtkIdType ptId, int size)
  {
  int newSize;
  vtkIdType *pointIds;

  newSize = this->NPoints + size;
  pointIds = new vtkIdType[newSize];
  memcpy(pointIds, this->PointIds,this->NPoints*sizeof(vtkIdType));
  delete [] this->PointIds;
  this->PointIds = NULL;

  this->PointIds = pointIds;

  this->NPoints = newSize;
  }
