getMaterialIndices(void) const
{
  if (PRIVATE(this)->materialIndices.getLength()) return PRIVATE(this)->materialIndices.getArrayPtr();
  return NULL;
}
