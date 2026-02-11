GetMediaStorage() const
{


  const Tag tsopclassuid(0x0008, 0x0016);
  if( !FindDataElement( tsopclassuid) )
    {
    gdcmDebugMacro( "No SOP Class UID" );
    return MediaStorage::MS_END;
    }
  const DataElement &de = GetDataElement(tsopclassuid);
  if( de.IsEmpty() )
    {
    gdcmDebugMacro( "Empty SOP Class UID" );
    return MediaStorage::MS_END;
    }
  std::string ts;
    {
    const ByteValue *bv = de.GetByteValue();
    assert( bv );
    if( bv->GetPointer() && bv->GetLength() )
      {

      ts = std::string(bv->GetPointer(), bv->GetLength());
      }
    }

  if( ts.size() )
    {
    char &last = ts[ts.size()-1];
    if( last == ' ' )
      {
      gdcmWarningMacro( "Media Storage Class UID: " << ts << " contained a trailing space character" );
      last = '\0';
      }
    }
  gdcmDebugMacro( "TS: " << ts );
  MediaStorage ms = MediaStorage::GetMSType(ts.c_str());
  if( ms == MediaStorage::MS_END )
    {
    gdcmWarningMacro( "Media Storage Class UID: " << ts << " is unknown" );
    }
  return ms;
}
