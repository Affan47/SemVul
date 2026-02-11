ReadIntoBuffer(char *buffer, size_t buflen)
{
  size_t thelen = ComputeBufferLength();
  if( thelen == 0 )
    {

    gdcmDebugMacro( "Cannot load an image of 0 bytes" );
    return false;
    }
   if( buflen < thelen )
    {
    gdcmDebugMacro( "buffer cannot be smaller than computed buffer length" );
    return false;
    }
  assert( Internals->GetFileOffset() != std::streampos(-1) );
  gdcmDebugMacro( "Using FileOffset: " << Internals->GetFileOffset() );
  std::istream* theStream = GetStreamPtr();
  theStream->seekg( Internals->GetFileOffset() );

  bool success = false;
  if( !success ) success = ReadRAWIntoBuffer(buffer, buflen);
  if( !success ) success = ReadRLEIntoBuffer(buffer, buflen);
  if( !success ) success = ReadJPEGIntoBuffer(buffer, buflen);
  if( !success ) success = ReadJPEGLSIntoBuffer(buffer, buflen);
  if( !success ) success = ReadJPEG2000IntoBuffer(buffer, buflen);

  return success;
}
