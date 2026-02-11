MakeIndexFromName(const DataObjectIdentifierType & name) const
{
  DataObjectIdentifierType baseName = "_";
  DataObjectPointerArraySizeType baseSize = baseName.size();
  if( name.size() <= baseSize || name.substr(0, baseSize) != baseName )
    {
    itkDebugMacro("MakeIndexFromName("<<name<<") -> exception bad base name");
    itkExceptionMacro(<<"Not an indexed data object: " << name);
    }
  DataObjectIdentifierType idxStr = name.substr(baseSize);
  DataObjectPointerArraySizeType idx;
  if( !(std::istringstream(idxStr) >> idx) )
    {
    itkDebugMacro("MakeIndexFromName("<<name<<") -> exception not an index");
    itkExceptionMacro(<<"Not an indexed data object: " << name);
    }
  itkDebugMacro("MakeIndexFromName("<<name<<") -> "<< idx);
  return idx;
}
