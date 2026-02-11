IsIndexedInputName(const DataObjectIdentifierType & name) const
{
  if( name == m_IndexedInputs[0]->first )
    {
    return true;
    }
  for (  DataObjectPointerArraySizeType i = 0; i < m_IndexedInputs.size(); ++i)
    {
    if ( m_IndexedInputs[i]->first == name )
      {
      return true;
      }
    }
  return false;
}
