BALCPProtect(DataSet &ds, Tag const & tag, IOD const & iod)
{

  assert( ds.FindDataElement(tag) );

  AnonymizeEvent ae;
  ae.SetTag( tag );
  this->InvokeEvent( ae );


  bool canempty = CanEmptyTag( tag, iod );
  if( !canempty )
    {
    DataElement copy;
    copy = ds.GetDataElement( tag );

    if ( IsVRUI( tag ) )
      {
      std::string UIDToAnonymize = "";
      UIDGenerator uid;

      if( !copy.IsEmpty() )
        {
        if( const ByteValue *bv = copy.GetByteValue() )
          {
          UIDToAnonymize = std::string( bv->GetPointer(), bv->GetLength() );
          }
        }

      std::string anonymizedUID = "";
      if( !UIDToAnonymize.empty() )
        {
        if ( dummyMapUIDTags.count( UIDToAnonymize ) == 0 )
          {
          anonymizedUID = uid.Generate();
          dummyMapUIDTags[ UIDToAnonymize ] = anonymizedUID;
          }
        else
          {
          anonymizedUID = dummyMapUIDTags[ UIDToAnonymize ];
          }
        }
      else
        {


        anonymizedUID = uid.Generate();
        }

      copy.SetByteValue( anonymizedUID.c_str(), (uint32_t)anonymizedUID.size() );
      ds.Replace( copy );
      }
    else
      {
      TagValueKey tvk;
      tvk.first = tag;

      assert( dummyMapNonUIDTags.count( tvk ) == 0 || dummyMapNonUIDTags.count( tvk ) == 1 );
      if( dummyMapNonUIDTags.count( tvk ) == 0 )
        {
        const char *ret = DummyValueGenerator::Generate( tvk.second.c_str() );
        if( ret )
          {
          dummyMapNonUIDTags[ tvk ] = ret;
          }
        else
          dummyMapNonUIDTags[ tvk ] = "";
        }

      std::string &v = dummyMapNonUIDTags[ tvk ];
      copy.SetByteValue( v.c_str(), (uint32_t)v.size() );
      }
      ds.Replace( copy );
    }
  else
    {

    DataElement copy = ds.GetDataElement( tag );
    copy.Empty();
    ds.Replace( copy );
    }
  return true;
}
