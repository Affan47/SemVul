ReadSymmetricTensorBufferAsBinary( std::istream & is,
  void * buffer,
  StreamingImageIOBase::SizeType num )
{
  std::streamsize bytesRemaining = num;
  const SizeType  componentSize = this->GetComponentSize();
  SizeType        pixelSize = componentSize * 6;

  if( this->GetNumberOfComponents() != 6 )
    {
    itkExceptionMacro(<< "Unsupported tensor dimension.");
    }
  while( bytesRemaining )
    {

    is.read( static_cast< char * >(buffer), 3 * componentSize );
    buffer = static_cast< char * >(buffer) + 3 * componentSize;

    is.seekg( componentSize, std::ios::cur );
    is.read( static_cast< char * >(buffer), 2 * componentSize );
    buffer = static_cast< char * >(buffer) + 2 * componentSize;

    is.seekg( 2 * componentSize, std::ios::cur );
    is.read( static_cast< char * >(buffer), componentSize );
    buffer = static_cast< char * >(buffer) + componentSize;
    bytesRemaining -= pixelSize;
    }

  if( is.fail() )
    {
    itkExceptionMacro(<< "Failure during writing of file.");
    }
}
