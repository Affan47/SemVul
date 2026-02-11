AddRequiredInputName( const DataObjectIdentifierType & name )
{
  if( name.empty() )
    {
    itkExceptionMacro("An empty string can't be used as an input identifier");
    }

  if( !m_RequiredInputNames.insert( name ).second )
    {
    return false;
    }


  m_Inputs.insert( DataObjectPointerMap::value_type(name, DataObjectPointer() ) );

  if( name == m_IndexedInputs[0]->first && m_NumberOfRequiredInputs == 0 )
    {
    m_NumberOfRequiredInputs = 1;
    }
  this->Modified();
  return true;
}
