FindOrAddNamedChild(const QName& name) {
  XmlElement* child = FirstNamed(name);
  if (!child) {
    child = new XmlElement(name);
    AddElement(child);
  }

  return child;
}
