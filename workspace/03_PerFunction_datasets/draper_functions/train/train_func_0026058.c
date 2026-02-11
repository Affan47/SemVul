ClearUserFields()
  {

  FieldsContainerType::iterator  it  = m_UserDefinedWriteFields.begin();
  FieldsContainerType::iterator  end = m_UserDefinedWriteFields.end();
  while( it != end )
    {
    MET_FieldRecordType* field = *it;
    it++;
    delete field;
    }


  it  = m_UserDefinedReadFields.begin();
  end = m_UserDefinedReadFields.end();
  while( it != end )
    {
    MET_FieldRecordType* field = *it;


    bool deleted = false;
    FieldsContainerType::iterator  it2  = m_UserDefinedWriteFields.begin();
    FieldsContainerType::iterator  end2 = m_UserDefinedWriteFields.end();
    while( it2 != end2 )
      {
      if(*it2 == *it)
        {
        deleted = true;
        break;
        }
      it2++;
      }

    it++;

    if(!deleted)
      {
      delete field;
      }
    }

  m_UserDefinedWriteFields.clear();
  m_UserDefinedReadFields.clear();
  }
