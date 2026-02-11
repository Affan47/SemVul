SetAsObjectBase(vtkInformationKey* key,
                                     vtkObjectBase* newvalue)
{
  if(!key)
    {
    return;
    }
  typedef vtkInformationInternals::MapType MapType;
  MapType::iterator i = this->Internal->Map.find(key);
  if(i != this->Internal->Map.end())
    {
    vtkObjectBase* oldvalue = i->second;
    if(newvalue)
      {
      i->second = newvalue;
      newvalue->Register(0);
      }
    else
      {
      this->Internal->Map.erase(i);
      }
    oldvalue->UnRegister(0);
    }
  else if(newvalue)
    {
    MapType::value_type entry(key, newvalue);
    this->Internal->Map.insert(entry);
    newvalue->Register(0);
    }
  this->Modified(key);
}
