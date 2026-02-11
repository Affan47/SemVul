GetIODFromFile(const File& file) const
{
  MediaStorage ms;
  ms.SetFromFile(file);

  const IODs &iods = GetIODs();
  const char *iodname = GetIODNameFromMediaStorage( ms );
  if( !iodname )
    {
    gdcmErrorMacro( "Not implemented: " << ms );
    throw "Not Implemented";
    }
  const IOD &iod = iods.GetIOD( iodname );
  return iod;
}
