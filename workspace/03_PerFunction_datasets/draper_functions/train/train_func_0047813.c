pushNode(const std::string& name, const str_pair_vec& params) {
  XMLParent *p = new XMLParent(name);
  for (size_t i=0; i<params.size(); i++) {
    p->params[params[i].first] = params[i].second;
  }
  if (s.empty()) {
    top = p;
  } else {
    s.top()->children.push_back(p);
  }
  s.push(p);
}
