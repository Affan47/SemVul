RemoveOutput(const DataObjectIdentifierType & key)
{

  if ( key == m_IndexedOutputs[0]->first )
    {
    this->SetOutput( key, ITK_NULLPTR );
    return;
    }


  for ( DataObjectPointerArraySizeType i = 1; i <  m_IndexedOutputs.size(); ++i )
    {
    if ( m_IndexedOutputs[i]->first == key )
      {
      this->SetNthOutput(i, ITK_NULLPTR);
      if ( i == m_IndexedOutputs.size() - 1 )
        {

        this->SetNumberOfIndexedOutputs( this->GetNumberOfIndexedOutputs() -1 );
        }
      return;
      }
    }


  DataObjectPointerMap::iterator it = m_Outputs.find(key);

  if ( it != m_Outputs.end() )
    {

    it->second->DisconnectSource( this, it->first );
    m_Outputs.erase( it );

    this->Modified();
    }
}
