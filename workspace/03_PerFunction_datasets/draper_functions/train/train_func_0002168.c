FindNestedElementWithName(const char* name)
{
  if (!name)
    {
    return 0;
    }

  int i;
  for(i=0;i < this->NumberOfNestedElements;++i)
    {
    const char* nname = this->NestedElements[i]->GetName();
    if(nname && (strcmp(nname, name) == 0))
      {
      return this->NestedElements[i];
      }
    }
  return 0;
}
