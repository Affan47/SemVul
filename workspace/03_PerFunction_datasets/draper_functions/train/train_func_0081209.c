followSiblingRef(unsigned long i, NodePtr &ptr) const
{
  if (i < chunk()->size - index_ - 1) {
    if (canReuse(ptr))
      ((DataNode *)this)->index_ += 1 + size_t(i);
    else
      ptr.assign(new DataNode(grove(), chunk(), index_ + size_t(i) + 1));
    return accessOK;
  }
  return ChunkNode::followSiblingRef(i - (chunk()->size - index_ - 1), ptr);
}
