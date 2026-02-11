pushText(const std::string& text) {
  XMLText *t = new XMLText(text);
  if (s.size() == 0) {
    top = t;
  } else {
    s.top()->children.push_back(t);
  }
}
