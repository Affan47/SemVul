signature ( const bool force_ ) const
{
 Lock lock(&_imgRef->_mutexLock);


  if ( force_ ||
       !GetImageProperty(constImage(), "Signature") ||
       constImage()->taint )
    {
      SignatureImage( const_cast<MagickCore::Image *>(constImage()) );
    }

  const char *property = GetImageProperty(constImage(), "Signature");

  return std::string( property );
}
