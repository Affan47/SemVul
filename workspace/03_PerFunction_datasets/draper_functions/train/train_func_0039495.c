UpdateLookup()
{
  if (!this->Lookup)
    {
    this->Lookup = new vtkVariantArrayLookup();
    this->Lookup->SortedArray = vtkVariantArray::New();
    this->Lookup->IndexArray = vtkIdList::New();
    }
  if (this->Lookup->Rebuild)
    {
    int numComps = this->GetNumberOfComponents();
    vtkIdType numTuples = this->GetNumberOfTuples();
    this->Lookup->SortedArray->DeepCopy(this);
    this->Lookup->IndexArray->SetNumberOfIds(numComps*numTuples);
    for (vtkIdType i = 0; i < numComps*numTuples; i++)
      {
      this->Lookup->IndexArray->SetId(i, i);
      }
    vtkSortDataArray::Sort(this->Lookup->SortedArray, this->Lookup->IndexArray);
    this->Lookup->Rebuild = false;
    this->Lookup->CachedUpdates.clear();
    }
}
