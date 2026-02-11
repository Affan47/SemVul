AddDefinition(const char* name, const char* value)
{
  if (!value )
    {
    return;
    }

#ifdef CMAKE_STRICT
  if (this->GetCMakeInstance())
    {
    this->GetCMakeInstance()->
      RecordPropertyAccess(name,cmProperty::VARIABLE);
    }
#endif

  this->Internal->VarStack.top().Set(name, value);
  if (this->Internal->VarUsageStack.size() &&
      this->VariableInitialized(name))
    {
    this->CheckForUnused("changing definition", name);
    this->Internal->VarUsageStack.top().erase(name);
    }
  this->Internal->VarInitStack.top().insert(name);

#ifdef CMAKE_BUILD_WITH_CMAKE
  cmVariableWatch* vv = this->GetVariableWatch();
  if ( vv )
    {
    vv->VariableAccessed(name,
                         cmVariableWatch::VARIABLE_MODIFIED_ACCESS,
                         value,
                         this);
    }
#endif
}
