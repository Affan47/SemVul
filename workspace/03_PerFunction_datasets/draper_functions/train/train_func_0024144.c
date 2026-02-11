InsertNextPoint(vtkIdType inputPtId,
                                                             double x[3])
{
  if ( (this->CurrentPointId+1) >= (vtkIdType)this->PointInfo->size() )
    {
    this->PointInfo->resize(2*this->PointInfo->size());
    }

  double *ptr = this->Points->WritePointer(3*this->CurrentPointId,3);
  *ptr++ = *x++;
  *ptr++ = *x++;
  *ptr   = *x;

  this->OutputPD->CopyData(this->InputPD,inputPtId,this->CurrentPointId);
  (*this->PointInfo)[this->CurrentPointId] = inputPtId;

  return this->CurrentPointId++;
}
