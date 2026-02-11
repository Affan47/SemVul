create(const MDL_key *mdl_key)
{
  switch (mdl_key->mdl_namespace())
  {
    case MDL_key::GLOBAL:
    case MDL_key::SCHEMA:
    case MDL_key::COMMIT:
      return new MDL_scoped_lock(mdl_key);
    default:
      return new MDL_object_lock(mdl_key);
  }
}
