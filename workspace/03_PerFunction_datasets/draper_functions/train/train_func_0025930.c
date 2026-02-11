getNotationName(GroveString &str) const
{
  const ExternalDataEntity *x = entity_->asExternalDataEntity();
  if (!x || !x->notation())
    return accessNull;
  setString(str, x->notation()->name());
  return accessOK;
}
