elementTypeOrigName(const ElementType *type,
						     StringC &buf)
{
  if (type->index() < elementTypeOrigNames_.size()
      && elementTypeOrigNames_[type->index()].size() > 0)
    return elementTypeOrigNames_[type->index()];
  else
    return generalName(type->name(), buf);
}
