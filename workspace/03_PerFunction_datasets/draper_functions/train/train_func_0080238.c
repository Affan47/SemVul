IsAnchoredAtEnd() {
  ZoneList<RegExpTree*>* nodes = this->nodes();
  for (int i = nodes->length() - 1; i >= 0; i--) {
    RegExpTree* node = nodes->at(i);
    if (node->IsAnchoredAtEnd()) { return true; }
    if (node->max_match() > 0) { return false; }
  }
  return false;
}
