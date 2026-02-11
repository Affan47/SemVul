isAssociated()
{
  if (!_function) return false;

  return _function->association(rtti())==this;
}
