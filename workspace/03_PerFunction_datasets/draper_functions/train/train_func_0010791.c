lookupDtd(const StringC &name)
{
  for (size_t i = 0; i < dtd_.size(); i++)
    if (dtd_[i]->name() == name)
      return dtd_[i];
  return Ptr<Dtd>();
}
