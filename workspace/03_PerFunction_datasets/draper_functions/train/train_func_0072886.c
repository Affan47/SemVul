AddSeriesDirectoryRecord()
{
  DataSet &rootds = GetFile().GetDataSet();
  Scanner const & scanner = GetScanner();

  Attribute<0x20,0xe> seriesinstanceuid;
  Scanner::ValuesType seriesinstanceuids = scanner.GetValues( seriesinstanceuid.GetTag() );

  const DataElement &de = rootds.GetDataElement( Tag(0x4,0x1220) );

  SmartPointer<SequenceOfItems> sqi = de.GetValueAsSQ();

  Scanner::ValuesType::const_iterator it = seriesinstanceuids.begin();
  for( ; it  != seriesinstanceuids.end(); ++it)
    {
    Item item;
    item.SetVLToUndefined();
    DataSet &ds = item.GetNestedDataSet();

    Attribute<0x4,0x1400> offsetofthenextdirectoryrecord = {0};
    ds.Insert( offsetofthenextdirectoryrecord.GetAsDataElement() );
    Attribute<0x4,0x1410> recordinuseflag = {0xFFFF};
    ds.Insert( recordinuseflag.GetAsDataElement() );
    Attribute<0x4,0x1420> offsetofreferencedlowerleveldirectoryentity = {0};
    ds.Insert( offsetofreferencedlowerleveldirectoryentity.GetAsDataElement() );
    Attribute<0x4,0x1430> directoryrecordtype;
    directoryrecordtype.SetValue( "SERIES" );
    ds.Insert( directoryrecordtype.GetAsDataElement() );
    const char *seriesuid = it->c_str();
    if( ! (seriesuid && *seriesuid) )
      {
      const char *fn = scanner.GetFilenameFromTagToValue(seriesinstanceuid.GetTag(), seriesuid);
      gdcmErrorMacro( "Missing Study Instance UID from file: " << fn );
      (void)fn;
      return false;
      }
    gdcmAssertAlwaysMacro( seriesuid && *seriesuid );
    seriesinstanceuid.SetValue( seriesuid );
    ds.Insert( seriesinstanceuid.GetAsDataElement() );

    Scanner::TagToValue const &ttv = scanner.GetMappingFromTagToValue(seriesinstanceuid.GetTag(), seriesuid);
    Attribute<0x8,0x60> modality;
    if( ttv.find( modality.GetTag() ) != ttv.end() )
      {
      modality.SetValue( ttv.find(modality.GetTag())->second );
      ds.Insert( modality.GetAsDataElement() );
      }
    Attribute<0x20,0x11> seriesnumber;
    if( ttv.find( seriesnumber.GetTag() ) != ttv.end() )
      {
      seriesnumber.SetValue( atoi(ttv.find(seriesnumber.GetTag())->second) );
      ds.Insert( seriesnumber.GetAsDataElement() );
      }

    sqi->AddItem( item );
    }

  return true;
}
