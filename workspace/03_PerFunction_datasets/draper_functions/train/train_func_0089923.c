SetNumberOfTableValues(vtkIdType number)
{
  if (this->NumberOfColors == number)
    {
    return;
    }
  this->Modified();
  this->NumberOfColors = number;
  this->Table->SetNumberOfTuples(number);
}
