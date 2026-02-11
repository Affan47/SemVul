accept(NodeVisitor &visitor)
{
  if (iter_.type() == TextItem::sdata)
    visitor.sdata(*this);
  else
    visitor.dataChar(*this);
}
