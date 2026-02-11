Allocate(vtkIdType sz, vtkIdType vtkNotUsed(ext))
{
  if ( sz > this->Size || this->Array != NULL )
    {
    delete [] this->Array;

    this->Size = ( sz > 0 ? sz : 1);
    if ( (this->Array = new voidPtr[this->Size]) == NULL )
      {
      return 0;
      }
    }

  this->NumberOfPointers = 0;

  return 1;
}
