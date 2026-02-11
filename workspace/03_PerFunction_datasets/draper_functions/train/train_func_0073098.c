GetUserDefinedNameByIndex(unsigned int idx)
    {
    if( idx < UserDefinedValuePool.size() )
      {
      UserDefinedValues::const_iterator it = UserDefinedValuePool.begin();
      while( idx )
        {
        it++;
        idx--;
        }
      return it->Name.c_str();
      }
    return NULL;
    }
