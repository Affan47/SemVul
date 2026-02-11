_getType_GCIO (
                                               GCExportFileH* hGXT,
                                               int where
                                             )
{
  CPLList* e;

  if( (e= CPLListGet(GetMetaTypes_GCIO(GetGCMeta_GCIO(hGXT)),where)) )
    return (GCType*)CPLListGetData(e);
  return NULL;
}
