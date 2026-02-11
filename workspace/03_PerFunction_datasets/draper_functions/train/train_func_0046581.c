compact()
{
  if (fLoadValue && fValue)
  {
    delete[] fValue;
    fValue = NULL;
    setTransferredBytes(0);
  }
}
