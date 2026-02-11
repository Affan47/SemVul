GetEdgeIndex(vtkIdType e_id) const
{
  vtkIdType index = e_id;
  int numProcs
    = this->Graph->GetInformation()->Get(vtkDataObject::DATA_NUMBER_OF_PIECES());

  if (numProcs > 1)
    {

    index = (e_id << this->procBits) >> this->procBits;
    }

  return index;
}
