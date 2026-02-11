GetCellArrayStatus(int index)
{
  int n = this->MetaData->GetOriginalNumberOfCellArrays();

  if ((index >= 0) && (index < n))
    {
    return this->MetaData->GetCellArrayStatus(index);
    }

  return 0;
}
