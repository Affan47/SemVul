Allocate(const vtkIdType sz, const vtkIdType ext)
{
  int i;
  int status = 0;

  for ( i=0; i < this->GetNumberOfArrays(); i++ )
    {
    if ( (status = this->Data[i]->Allocate(sz,ext)) == 0 )
      {
      break;
      }
    }

  return status;
}
