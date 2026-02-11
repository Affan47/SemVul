MET_GetFieldRecord(const char * _fieldName,
                   METAIO_STL::vector<MET_FieldRecordType *> * _fields)
  {
  METAIO_STL::vector<MET_FieldRecordType *>::iterator fieldIter;
  for(fieldIter=_fields->begin(); fieldIter!=_fields->end(); ++fieldIter)
    {
    if(!strcmp((*fieldIter)->name, _fieldName))
      {
      return *fieldIter;
      }
    }
  return NULL;
  }
