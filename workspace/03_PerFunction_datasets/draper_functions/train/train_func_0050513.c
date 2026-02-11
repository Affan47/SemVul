setNodePtrAttributeOrigin(NodePtr &ptr,
						 const BaseNode *node) const
{
  ptr.assign(new EntityNode(node->grove(), entity_));
  return accessOK;
}
