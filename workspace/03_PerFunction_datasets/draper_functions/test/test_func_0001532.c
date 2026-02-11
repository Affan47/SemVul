_findTypeByName_GCIO (
                                               GCExportFileH* hGXT,
                                               const char* typName
                                             )
{
  GCType* theClass;
  GCExportFileMetadata* header;

  header= GetGCMeta_GCIO(hGXT);
  if( GetMetaTypes_GCIO(header) )
  {
    CPLList* e;
    int n, i;
    if( (n= CPLListCount(GetMetaTypes_GCIO(header)))>0 )
    {
      if( *typName=='*' ) return 0;
      for( i = 0; i < n; i++)
      {
        if( (e= CPLListGet(GetMetaTypes_GCIO(header),i)) )
        {
          if( (theClass= (GCType*)CPLListGetData(e)) )
          {
            if( EQUAL(GetTypeName_GCIO(theClass),typName) )
            {
              return i;
            }
          }
        }
      }
    }
  }
  return -1;
}
