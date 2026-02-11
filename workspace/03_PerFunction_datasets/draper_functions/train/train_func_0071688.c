get_node(XMLNode& parent,const char* name) {
  XMLNode n = parent[name];
  if(!n) n=parent.NewChild(name);
  return n;
}
