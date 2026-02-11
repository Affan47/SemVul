GetUserField(const char* _name)
{
  FieldsContainerType::iterator  it  = m_UserDefinedWriteFields.begin();
  FieldsContainerType::iterator  end = m_UserDefinedWriteFields.end();
  while( it != end )
  {
    int eSize;
    MET_SizeOfType((*it)->type, &eSize);
    const unsigned int itLength =
                static_cast<unsigned int>( (*it)->length );
    void * out;
    if(!strcmp((*it)->name,_name))
      {
      if((*it)->type == MET_STRING)
        {
        out = (void*) (new char[(itLength+1)*eSize] );
        memcpy( out, (*it)->value, itLength * eSize );
        static_cast<char*>(out)[itLength]=0;
        }
      else if((*it)->type == MET_FLOAT_MATRIX)
        {
        const unsigned int numMatrixElements = itLength * itLength;
        out = (void*) (new char[numMatrixElements*eSize] );
        for( unsigned int i=0; i < numMatrixElements; i++ )
          {
          MET_DoubleToValue((*it)->value[i],(*it)->type,out,i);
          }
        }
      else
        {
        out = (void*) (new char[itLength*eSize] );
        for( unsigned int i=0; i < itLength; i++ )
          {
          MET_DoubleToValue((*it)->value[i],(*it)->type,out,i);
          }
        }
      return out;
      }
    ++it;
  }
  return NULL;
}
