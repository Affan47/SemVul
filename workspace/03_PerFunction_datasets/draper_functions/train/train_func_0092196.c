GetReferenceValueForDirectoryType(size_t itemidx)
{


  MyPair ret;
  const SequenceOfItems *sqi = GetDirectoryRecordSequence();
  const Item &item = sqi->GetItem(itemidx);
  const DataSet &ds = item.GetNestedDataSet();
  Attribute<0x4,0x1430> directoryrecordtype;
  directoryrecordtype.Set( ds );

  const char *input = directoryrecordtype.GetValue();
  assert( input );

  if( strcmp( input, "PATIENT " ) == 0 )
    {
    Attribute<0x10,0x20> patientid;
    patientid.Set( ds );
    assert( patientid.GetValue() );
    ret.first = patientid.GetValue();
    ret.second = patientid.GetTag();
    }
  else if( strcmp( input, "STUDY ") == 0 )
    {
    Attribute <0x20,0xd> studyuid;
    studyuid.Set( ds );
    assert( studyuid.GetValue() );
    ret.first = studyuid.GetValue();
    ret.second = studyuid.GetTag();
    }
  else if( strcmp( input, "SERIES" ) == 0 )
    {
    Attribute <0x20,0xe> seriesuid;
    seriesuid.Set( ds );
    assert( seriesuid.GetValue() );
    ret.first = seriesuid.GetValue();
    ret.second = seriesuid.GetTag();
    }
  else if( strcmp( input, "IMAGE " ) == 0 )
    {
    Attribute <0x04,0x1511> sopuid;
    sopuid.Set( ds );
    assert( sopuid.GetValue() );
    ret.first = sopuid.GetValue();
    ret.second = Tag(0x8,0x18);
    }
  else
    {
    assert( 0 );
    }
  return ret;
}
