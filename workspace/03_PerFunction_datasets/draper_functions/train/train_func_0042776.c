children(NodeListPtr &ptr) const
{
  NodePtr head;
  AccessResult ret = firstChild(head);
  switch (ret) {
  case accessOK:
    ptr.assign(new SiblingNodeList(head));
    break;
  case accessNull:
    ptr.assign(new BaseNodeList);
    ret = accessOK;
    break;
  default:
    break;
  }
  return ret;
}
