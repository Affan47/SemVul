AddSubTypeField_GCIO (
                                                GCExportFileH* H,
                                                const char* typName,
                                                const char* subtypName,
                                                int where,
                                                const char* name,
                                                long id,
                                                GCTypeKind knd,
                                                const char* extra,
                                                const char* enums
                                              )
{
  int whereClass, whereSubType;
  GCType* theClass;
  GCSubType* theSubType;
  GCField* theField;
  CPLList* L;
  const char* normName;

  if( (whereClass= _findTypeByName_GCIO(H,typName))==-1 )
  {
    CPLError( CE_Failure, CPLE_AppDefined,
              "failed to find a Geoconcept type for '%s.%s@%s#%ld'.\n",
              typName, subtypName, name, id);
    return NULL;
  }
  theClass= _getType_GCIO(H,whereClass);

  if( (whereSubType= _findSubTypeByName_GCIO(theClass,subtypName))==-1 )
  {
    CPLError( CE_Failure, CPLE_AppDefined,
              "failed to find a Geoconcept subtype for '%s.%s@%s#%ld'.\n",
              typName, subtypName, name, id);
    return NULL;
  }
  theSubType= _getSubType_GCIO(theClass,whereSubType);

  normName= _NormalizeFieldName_GCIO(name);
  if( _findFieldByName_GCIO(GetSubTypeFields_GCIO(theSubType),normName)!=-1 )
  {
    CPLError( CE_Failure, CPLE_AppDefined,
              "field '%s.%s@%s#%ld' already exists.\n",
              typName, subtypName, name, id);
    return NULL;
  }

  if( !(theField= _CreateField_GCIO(normName,id,knd,extra,enums)) )
  {
    return NULL;
  }
  if(
      where==-1 ||
      (where==0 && CPLListCount(GetSubTypeFields_GCIO(theSubType))==0)
    )
  {
    L= CPLListAppend(GetSubTypeFields_GCIO(theSubType),theField);
  }
  else
  {
    L= CPLListInsert(GetSubTypeFields_GCIO(theSubType),theField,where);
  }
  if( !L )
  {
    _DestroyField_GCIO(&theField);
    CPLError( CE_Failure, CPLE_OutOfMemory,
              "failed to add a Geoconcept field for '%s.%s@%s#%ld'.\n",
              typName, subtypName, name, id);
    return NULL;
  }
  SetSubTypeFields_GCIO(theSubType, L);

  CPLDebug("GEOCONCEPT", "Field '%s.%s@%s#%ld' added.", typName, subtypName, name, id);

  return theField;
}
