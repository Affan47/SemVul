duplicate(RequestAttribute& req_attr) {
  id = req_attr.getAttributeId();
  type = req_attr.getDataType();
  issuer = req_attr.getIssuer();
  node_ = req_attr.getNode();
  attrval = (req_attr.getAttributeFactory())->createValue(node_, type);
  return *this;
}
