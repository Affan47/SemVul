has(const std::string& tag) const
{
  if (resmap_rep.find(tag) == resmap_rep.end())
    return false;
  return true;
}
