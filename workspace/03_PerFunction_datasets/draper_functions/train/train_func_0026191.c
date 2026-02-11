GetCurrentDataObject()
{
  if (!this->IsDoneWithTraversal())
    {
    return this->Internals->Iterator->GetCurrentDataObject();
    }

  return 0;
}
