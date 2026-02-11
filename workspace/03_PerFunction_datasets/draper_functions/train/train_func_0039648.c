SetNumberOfTuples(const vtkIdType number)
{
  for ( int i=0; i < this->GetNumberOfArrays(); i++ )
    {
    this->Data[i]->SetNumberOfTuples(number);
    }
}
