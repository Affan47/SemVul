GetInputNames() const
{
  NameArray res;
  res.reserve(m_Inputs.size());
  for ( DataObjectPointerMap::const_iterator it = m_Inputs.begin(); it != m_Inputs.end(); ++it )
    {

    if ( it->first != m_IndexedInputs[0]->first
         || it->second.IsNotNull()
         || this->IsRequiredInputName(it->first) )
      {
      res.push_back( it->first );
      }
    }
  return res;
}
