chainsetup_names(void) const
{
  std::vector<std::string> result;
  std::vector<ECA_CHAINSETUP*>::const_iterator p = chainsetups_rep.begin();
  while(p != chainsetups_rep.end()) {
    result.push_back((*p)->name());
    ++p;
  }
  return result;
}
