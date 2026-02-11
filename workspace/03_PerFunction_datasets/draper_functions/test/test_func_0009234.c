ReadHeader_GCIO (
                                                        GCExportFileH* hGXT
                                                      )
{
  GCExportFileMetadata* Meta;

  if( _get_GCIO(hGXT)==EOF )
  {
    return NULL;
  }
  if( GetGCWhatIs_GCIO(hGXT)!=vPragma_GCIO )
  {
    CPLDebug( "GEOCONCEPT",
              "Geoconcept export badly formatted :"
              "%s expected.",
              kPragma_GCIO);
    return NULL;
  }
  SetGCMeta_GCIO(hGXT, CreateHeader_GCIO());
  if( (Meta= GetGCMeta_GCIO(hGXT))==NULL )
  {
    return NULL;
  }
  SetMetaExtent_GCIO(Meta, CreateExtent_GCIO(HUGE_VAL,HUGE_VAL,-HUGE_VAL,-HUGE_VAL));
  while( _get_GCIO(hGXT)!=EOF )
  {
    if( GetGCWhatIs_GCIO(hGXT)==vComType_GCIO )
    {
      continue;
    }
    if( GetGCWhatIs_GCIO(hGXT)==vPragma_GCIO )
    {

      if( !_parsePragma_GCIO(hGXT) )
      {
        return NULL;
      }

      if( GetGCStatus_GCIO(hGXT)!=vMemoStatus_GCIO )
      {
        continue;
      }
    }

    if( !_parseObject_GCIO(hGXT) )
    {
      return NULL;
    }
  }
  if( CPLListCount(GetMetaTypes_GCIO(Meta))==0 )
  {
    DestroyHeader_GCIO(&(GetGCMeta_GCIO(hGXT)));
    CPLError( CE_Failure, CPLE_AppDefined,
              "Geoconcept export syntax error at line %ld.\n",
              GetGCCurrentLinenum_GCIO(hGXT) );
    return NULL;
  }

  Rewind_GCIO(hGXT,NULL);

  CPLDebug( "GEOCONCEPT",
            "Metadata = (\n"
            "  nb Types : %d\n"
            "  Charset : %s\n"
            "  Delimiter : 0x%x\n"
            "  Unit : %s\n"
            "  Resolution : %g\n"
            "  Quoted-Text : %s\n"
            "  Format : %s\n"
            "  CoordSystemID : %d; TimeZoneValue : %d\n"
            ")",
            CPLListCount(GetMetaTypes_GCIO(Meta)),
            GCCharset2str_GCIO(GetMetaCharset_GCIO(Meta)),
            GetMetaDelimiter_GCIO(Meta),
            GetMetaUnit_GCIO(Meta),
            GetMetaResolution_GCIO(Meta),
            GetMetaQuotedText_GCIO(Meta)? "yes":"no",
            GetMetaFormat_GCIO(Meta)==1? "relative":"absolute",
            GetMetaSysCoord_GCIO(Meta)? GetSysCoordSystemID_GCSRS(GetMetaSysCoord_GCIO(Meta)):-1,
            GetMetaSysCoord_GCIO(Meta)? GetSysCoordTimeZone_GCSRS(GetMetaSysCoord_GCIO(Meta)):-1 );

  return Meta;
}
