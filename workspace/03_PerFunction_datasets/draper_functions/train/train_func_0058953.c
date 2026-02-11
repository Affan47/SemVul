createFn(const std::string& type){
  FnMap::iterator it;
  if((it=fnmap.find(type)) != fnmap.end())
    return (*it).second;
  else {
    std::string tp("string-equal");
    if((it=fnmap.find(tp)) != fnmap.end())
      return (*it).second;
  }
  return NULL;
}
