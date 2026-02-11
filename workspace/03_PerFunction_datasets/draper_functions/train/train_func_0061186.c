AppendProperty(const char* prop, const char* value, bool asString)
{
  if (!prop)
    {
    return;
    }


  if(strcmp(prop, "DEBUG_CONFIGURATIONS") == 0)
    {
    this->DebugConfigs.clear();
    }

  this->Properties.AppendProperty(prop, value, cmProperty::GLOBAL, asString);
}
