GetElementIndex(vtkIdType id)
{
  vtkIdType index = -1;
  int j;
  for (j=0; j<this->NElements; j++)
    {
    if (this->ElementIds[j] == id)
      {
      index = j;
      break;
      }
    }
  if (index == -1)
    {
    vtkErrorMacro("Error: ElementId not in sparse matrix");
    return -1;
    }
  return index;
}
