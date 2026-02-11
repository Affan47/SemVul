IsIndexedName(const DataObjectIdentifierType & name) const
{
  DataObjectIdentifierType baseName = "_";
  DataObjectPointerArraySizeType baseSize = baseName.size();
  if( name.size() <= baseSize || name.substr(0, baseSize) != baseName )
    {
    return false;
    }
  DataObjectIdentifierType idxStr = name.substr(baseSize);
  DataObjectPointerArraySizeType idx;
  return (std::istringstream(idxStr) >> idx);
}
