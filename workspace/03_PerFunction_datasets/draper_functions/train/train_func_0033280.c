Read(void *buffer)
{
  std::ifstream file;

  if ( this->RequestedToStream() )
    {
    itkAssertOrThrowMacro(m_FileType != ASCII, "Can not stream with ASCII type files");

    if( this->GetPixelType() == ImageIOBase::SYMMETRICSECONDRANKTENSOR )
      {
      itkExceptionMacro(<< "Cannot stream read binary second rank tensors.");
      }


    this->OpenFileForReading( file, this->m_FileName.c_str() );

    itkAssertOrThrowMacro(this->GetHeaderSize() != 0, "Header size is unknown when it shouldn't be!");
    this->StreamReadBufferAsBinary(file, buffer);

    switch ( this->GetComponentSize() )
      {
      case 1:
        break;
      case 2:
        ByteSwapper< uint16_t >::SwapRangeFromSystemToBigEndian( (uint16_t *)buffer, this->GetIORegionSizeInComponents() );
        break;
      case 4:
        ByteSwapper< uint32_t >::SwapRangeFromSystemToBigEndian( (uint32_t *)buffer, this->GetIORegionSizeInComponents() );
        break;
      case 8:
        ByteSwapper< uint64_t >::SwapRangeFromSystemToBigEndian( (uint64_t *)buffer, this->GetIORegionSizeInComponents() );
        break;
      default:
        itkExceptionMacro(<< "Unknown component size" << this->GetComponentSize());
      }
    }
  else
    {

    this->OpenFileForReading( file, this->m_FileName.c_str() );

    itkAssertOrThrowMacro(this->GetHeaderSize() != 0, "Header size is unknown when it shouldn't be!");

    if ( file.fail() )
      {
      itkExceptionMacro(<< "Failed seeking to data position");
      }


    std::streampos dataPos = static_cast< std::streampos >( this->GetHeaderSize() );
    file.seekg(dataPos, std::ios::beg);


    if ( m_FileType == ASCII )
      {
      this->ReadBufferAsASCII( file, buffer, this->GetComponentType(),
                               this->GetImageSizeInComponents()
                               );
      }
    else
      {

      if( this->GetPixelType() == ImageIOBase::SYMMETRICSECONDRANKTENSOR )
        {
        this->ReadSymmetricTensorBufferAsBinary( file, buffer, this->GetImageSizeInBytes() );
        }
      else
        {
        this->ReadBufferAsBinary( file, buffer, this->GetImageSizeInBytes() );
        }

      switch ( this->GetComponentSize() )
        {
        case 1:
          break;
        case 2:
          ByteSwapper< uint16_t >::SwapRangeFromSystemToBigEndian( (uint16_t *)buffer, this->GetImageSizeInComponents() );
          break;
        case 4:
          ByteSwapper< uint32_t >::SwapRangeFromSystemToBigEndian( (uint32_t *)buffer, this->GetImageSizeInComponents() );
          break;
        case 8:
          ByteSwapper< uint64_t >::SwapRangeFromSystemToBigEndian( (uint64_t *)buffer, this->GetImageSizeInComponents() );
          break;
        default:
          itkExceptionMacro(<< "Unknown component size" << this->GetComponentSize());
        }
      }
    }
}
