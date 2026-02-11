map_priority(const std::string& str1, const std::string& str2) {
  for(std::list< std::pair<Arc::RegularExpression,uint32_t> >::iterator p = priorities_map.begin();
                         p != priorities_map.end(); ++p) {
    if(p->first.match(str1) || p->first.match(str2)) return p->second;
  }
  return ARC_PLUGIN_DEFAULT_PRIORITY;
}
