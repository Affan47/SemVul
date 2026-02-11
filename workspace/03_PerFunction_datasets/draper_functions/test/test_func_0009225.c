operator[](std::string s)
{
  const_iterator i = _node_map.find(s);
  if (i != _node_map.end()) {
    return i->second;
  }else if (OPT::case_insensitive) {
    notstd::to_lower(&s);
    i = _node_map.find(s);
  }else{
    return NULL;
  }
  return (i != _node_map.end()) ? i->second : NULL;
}
