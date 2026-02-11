TextNamed(const QName& name) const {
  XmlChild* pChild;
  for (pChild = first_child_; pChild; pChild = pChild->next_child_) {
    if (!pChild->IsText() && pChild->AsElement()->Name() == name)
      return pChild->AsElement()->BodyText();
  }
  return std::string();
}
