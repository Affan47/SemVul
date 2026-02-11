_CreateType_GCIO (
                                                  const char* typName,
                                                  long id
                                                )
{
  GCType* theClass;

  if( !(theClass= CPLMalloc(sizeof(GCType))) )
  {
    CPLError( CE_Failure, CPLE_OutOfMemory,
              "failed to create a Geoconcept type for '%s#%ld'.\n",
              typName, id);
    return NULL;
  }
  _InitType_GCIO(theClass);
  SetTypeName_GCIO(theClass, CPLStrdup(typName));
  SetTypeID_GCIO(theClass, id);

  return theClass;
}
