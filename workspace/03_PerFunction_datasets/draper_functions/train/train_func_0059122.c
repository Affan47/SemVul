findNode(const std::string& domain, DomainNode* node)
{
  auto labels = splitDomainLabel(domain);
  for(auto i = labels.rbegin(), eoi = labels.rend(); i != eoi && node; ++i) {
    node = node->findNext(*i);
  }
  return node;
}
}
