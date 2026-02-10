GetAbstractArray(const char *arrayName, int &index)
{
  int i;
  const char *name;
  index = -1;
  if (!arrayName)
    {
    return NULL;
    }
  for (i=0; i < this->GetNumberOfArrays(); i++)
    {
    name = this->GetArrayName(i);
    if ( name && !strcmp(name,arrayName) )
      {
      index = i;
      return this->GetAbstractArray(i);
      }
    }
  return NULL;
}
