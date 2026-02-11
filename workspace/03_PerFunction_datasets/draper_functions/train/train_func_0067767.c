InsertTuple(vtkIdType i, const float * tuple)
{
  vtkIdType loc = this->NumberOfComponents*i;

  for (int j=0; j<this->NumberOfComponents; j++)
    {
    this->InsertValue(loc+j,static_cast<int>(tuple[j]));
    }
  this->DataChanged();
}
