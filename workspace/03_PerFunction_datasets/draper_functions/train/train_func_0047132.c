CreateViewElem(const std::string& name,
                                 const std::string& type) {
  buzz::XmlElement* view_elem =
      new buzz::XmlElement(QN_JINGLE_DRAFT_VIEW, true);
  view_elem->AddAttr(QN_NAME, name);
  view_elem->SetAttr(QN_TYPE, type);
  return view_elem;
}
