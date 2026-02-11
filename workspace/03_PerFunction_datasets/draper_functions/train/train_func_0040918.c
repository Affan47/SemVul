firstSibling(NodePtr &ptr) const
{
  if (canReuse(ptr))
    ((AttributeAsgnNode *)this)->attIndex_ = 0;
  else
    ptr.assign(makeAttributeAsgnNode(grove(), 0));
  return accessOK;
}
