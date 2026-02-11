PrefixForNs(const std::string& ns,
                                                     bool isattr) {
  if (ns == NS_XML)
    return std::make_pair(std::string("xml"), true);
  if (ns == NS_XMLNS)
    return std::make_pair(std::string("xmlns"), true);
  if (isattr ? ns == STR_EMPTY : PrefixMatchesNs(STR_EMPTY, ns))
    return std::make_pair(STR_EMPTY, true);

  std::vector<std::string>::iterator pos;
  for (pos = pxmlnsStack_->end(); pos > pxmlnsStack_->begin(); ) {
    pos -= 2;
    if (*(pos + 1) == ns &&
        (!isattr || !pos->empty()) && PrefixMatchesNs(*pos, ns))
      return std::make_pair(*pos, true);
  }

  return std::make_pair(STR_EMPTY, false);
}
