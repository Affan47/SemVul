AddPatientDirectoryRecord()
{
  gdcm::DataSet &rootds = GetFile().GetDataSet();
  gdcm::Scanner const & scanner = GetScanner();

  Attribute<0x10,0x20> patientid;
  gdcm::Scanner::ValuesType patientids = scanner.GetValues( patientid.GetTag() );


  const gdcm::DataElement &de = rootds.GetDataElement( Tag(0x4,0x1220) );

  SmartPointer<SequenceOfItems> sqi = de.GetValueAsSQ();

  gdcm::Scanner::ValuesType::const_iterator it = patientids.begin();
  for( ; it  != patientids.end(); ++it)
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
    directoryrecordtype.SetValue( "PATIENT" );
    ds.Insert( directoryrecordtype.GetAsDataElement() );
    const char *pid = it->c_str();
    if( ! (pid && *pid) )
      {
      const char *fn = scanner.GetFilenameFromTagToValue(patientid.GetTag(), pid);
      gdcmErrorMacro( "Missing Patient ID from file: " << fn );
      (void)fn;
      return false;
      }
    gdcmAssertAlwaysMacro( pid && *pid );
    patientid.SetValue( pid );
    ds.Insert( patientid.GetAsDataElement() );

    gdcm::Scanner::TagToValue const &ttv = scanner.GetMappingFromTagToValue(patientid.GetTag(), pid);
    Attribute<0x10,0x10> patientsname;
    if( ttv.find( patientsname.GetTag() ) != ttv.end() )
      {
      patientsname.SetValue( ttv.find(patientsname.GetTag())->second );
      ds.Insert( patientsname.GetAsDataElement() );
      }


    sqi->AddItem( item );
    }

  return true;
}
