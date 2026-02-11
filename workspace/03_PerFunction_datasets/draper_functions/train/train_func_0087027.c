CanonicalNode(Prefilter* node) {
  string node_string = NodeString(node);
  map<string, Prefilter*>::iterator iter = node_map_.find(node_string);
  if (iter == node_map_.end())
    return NULL;
  return (*iter).second;
}
