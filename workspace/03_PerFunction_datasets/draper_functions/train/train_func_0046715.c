createFn(const std::string& type){
  FnMap::iterator it;
  if((it=fnmap.find(type)) != fnmap.end())
    return (*it).second;
  else return NULL;
}
