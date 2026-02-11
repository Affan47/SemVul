isVariable() const
{
  return type() == ValueKeyword && keyword() == Variable;
}
