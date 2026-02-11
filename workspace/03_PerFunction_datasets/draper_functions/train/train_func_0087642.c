getAttributeEntity(const StringC &name,
						  const Location &)
{

  if (!metaDtd_.isNull())
    return metaDtd_->lookupEntity(0, name);
  return 0;
}
