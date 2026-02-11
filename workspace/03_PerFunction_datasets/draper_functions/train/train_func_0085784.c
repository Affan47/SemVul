AppendProperty(const char* prop,
                                                const char* value,
                                                bool asString)
{
  if(strcmp(prop, "TYPE") == 0)
    {
    this->Type = cmCacheManager::StringToType(value? value : "STRING");
    }
  else if(strcmp(prop, "VALUE") == 0)
    {
    if(value)
      {
      if(!this->Value.empty() && *value && !asString)
        {
        this->Value += ";";
        }
      this->Value += value;
      }
    }
  else
    {
    this->Properties.AppendProperty(prop, value, cmProperty::CACHE, asString);
    }
}
