ClearAdditionalFields()
  {

  FieldsContainerType::iterator it  = m_AdditionalReadFields.begin();
  FieldsContainerType::iterator end = m_AdditionalReadFields.end();
  while( it != end )
    {
    MET_FieldRecordType* field = *it;
    if( field )
      {
      delete field;
      }
    ++it;
    }

  m_AdditionalReadFields.clear();
  }
