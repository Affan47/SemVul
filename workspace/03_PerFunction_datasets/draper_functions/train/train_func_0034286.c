LookupValue(int value, vtkIdList* ids)
{
  this->UpdateLookup();

  if (value == 1)
    {
    ids->DeepCopy(this->Lookup->OneArray);
    }
  else if (value == 0)
    {
    ids->DeepCopy(this->Lookup->ZeroArray);
    }
  else
    {
    ids->Reset();
    }
}
