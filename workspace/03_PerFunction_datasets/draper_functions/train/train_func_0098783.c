dissect(const std::string& child,
                      std::string& destination) const {
  const XMLNode* c = getChild(child);
  if (c != 0) {
    destination = c->getText();
    return true;
  } else {
    return false;
  }
}
