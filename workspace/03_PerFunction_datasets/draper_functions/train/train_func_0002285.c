isChildArg(const char *infoName,
                                             const char *argText) const
{
  if (ArUtil::isStrEmpty(infoName) || ArUtil::isStrEmpty(argText)) {
    return false;
  }
  std::map<std::string, std::map<std::string, bool> >::const_iterator iter1 =
                              myInfoNameToMapOfChildArgsMap.find(infoName);
  if (iter1 == myInfoNameToMapOfChildArgsMap.end()) {
    return false;
  }

  std::map<std::string, bool>::const_iterator iter2 = iter1->second.find(argText);
  if (iter2 != iter1->second.end()) {
    return iter2->second;
  }

  return false;

}
