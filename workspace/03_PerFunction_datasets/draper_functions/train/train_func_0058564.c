SetFields(const TigerRecordInfo *psRTInfo,
                              OGRFeature      *poFeature,
                              char            *achRecord)
{
  int i;
  for (i=0; i<psRTInfo->nFieldCount; ++i) {
    if (psRTInfo->pasFields[i].bSet) {
      SetField( poFeature,
                psRTInfo->pasFields[i].pszFieldName,
                achRecord,
                psRTInfo->pasFields[i].nBeg,
                psRTInfo->pasFields[i].nEnd );
    }
  }
}
