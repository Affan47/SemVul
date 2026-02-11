GetOrCreateEntry(const std::string& id,
                                              bool create) {
  EntryMap::iterator it = map_.find(id);
  if (it != map_.end())
    return &it->second;
  if (!create)
    return NULL;
  Entry e;
  e.lock_state = LS_UNLOCKED;
  e.accessors = 0;
  e.size = 0;
  e.streams = 0;
  e.last_modified = time(0);
  it = map_.insert(EntryMap::value_type(id, e)).first;
  return &it->second;
}
