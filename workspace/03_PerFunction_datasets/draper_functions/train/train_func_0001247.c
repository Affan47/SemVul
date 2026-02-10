GetDefinition(const char* name) const
{
#ifdef CMAKE_STRICT
  if (this->GetCMakeInstance())
    {
    this->GetCMakeInstance()->
      RecordPropertyAccess(name,cmProperty::VARIABLE);
    }
#endif
  const char* def = 0;
  DefinitionMap::const_iterator pos =
    this->DefinitionStack.back().find(name);
  if(pos != this->DefinitionStack.back().end())
    {
    def = (*pos).second.c_str();
    }
  else
    {
    def = this->GetCacheManager()->GetCacheValue(name);
    }
#ifdef CMAKE_BUILD_WITH_CMAKE
  cmVariableWatch* vv = this->GetVariableWatch();
  if ( vv )
    {
    if ( def )
      {
      vv->VariableAccessed(name, cmVariableWatch::VARIABLE_READ_ACCESS,
        def, this);
      }
    else
      {

      DefinitionMap::const_iterator pos2 =
        this->DefinitionStack.back()
        .find("CMAKE_ALLOW_UNKNOWN_VARIABLE_READ_ACCESS");
      if (pos2 != this->DefinitionStack.back().end() &&
          cmSystemTools::IsOn((*pos2).second.c_str()))
        {
        vv->VariableAccessed(name,
          cmVariableWatch::ALLOWED_UNKNOWN_VARIABLE_READ_ACCESS, def, this);
        }
      else
        {
        vv->VariableAccessed(name,
          cmVariableWatch::UNKNOWN_VARIABLE_READ_ACCESS, def, this);
        }
      }
    }
#endif
  return def;
}
