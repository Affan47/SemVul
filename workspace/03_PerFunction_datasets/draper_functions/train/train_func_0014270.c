typeFromString(const char *text)
{
  if (ArUtil::isStrEmpty(text)) {
    return INVALID;
  }
  if (ourTextToTypeMap == NULL) {
    ourTextToTypeMap = new std::map<std::string, Type>();
    (*ourTextToTypeMap)["INVALID"] = INVALID;
    (*ourTextToTypeMap)["INT"] = INT;
    (*ourTextToTypeMap)["DOUBLE"] = DOUBLE;
    (*ourTextToTypeMap)["STRING"] = STRING;
    (*ourTextToTypeMap)["CPPSTRING"] = CPPSTRING;
    (*ourTextToTypeMap)["BOOL"] = BOOL;
    (*ourTextToTypeMap)["FUNCTOR"] = FUNCTOR;
    (*ourTextToTypeMap)["DESCRIPTION_HOLDER"] = DESCRIPTION_HOLDER;
    (*ourTextToTypeMap)["STRING_HOLDER"] = STRING_HOLDER;
    (*ourTextToTypeMap)["SEPARATOR"] = SEPARATOR;
    (*ourTextToTypeMap)["LIST"] = LIST;
    (*ourTextToTypeMap)["LIST_HOLDER"] = LIST_HOLDER;

  }

  std::map<std::string, Type>::iterator iter = ourTextToTypeMap->find(text);
  if (iter != ourTextToTypeMap->end()) {
    return iter->second;
  }
  return INVALID;

}
