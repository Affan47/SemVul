GetRightChild(vtkIdType loc)
{
  vtkIdType heapSize;
  heapSize = this->Heap->GetNumberOfIds();

  if ((loc<0)||(loc>=heapSize))
    {
    vtkErrorMacro(<< "Heap smaller than requested location.");
    return -1;
    }

  if (loc >= (heapSize-1)/2)
    return -1;

  return 2*loc + 2;
}
