ClearCache() {


  vector<State*> v;
  v.reserve(state_cache_.size());
  for (StateSet::iterator it = state_cache_.begin();
       it != state_cache_.end(); ++it)
    v.push_back(*it);
  state_cache_.clear();
  for (int i = 0; i < v.size(); i++)
    delete[] reinterpret_cast<const char*>(v[i]);
}
