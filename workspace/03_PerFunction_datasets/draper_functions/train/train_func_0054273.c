normaliseParamName(const std::string & name) {

  if( params_.find(name) == params_.end() )
    iterate(params_, i)
      if( i->second.abbrev == name )
        return i->first;
  return name;
}
