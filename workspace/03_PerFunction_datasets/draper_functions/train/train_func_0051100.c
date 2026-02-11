Write(const void *buffer)
{

  this->WriteImageInformation();


  voidp             p = const_cast< voidp >( buffer );
  const std::string ImageFileName = GetImageFileName(m_FileName);
  const std::string fileExt = GetExtension(m_FileName);


  if ( !fileExt.compare(".img.gz") )
    {

    gzFile file_p = gzopen(ImageFileName.c_str(), "wb");
    if ( file_p == NULL )
      {
      itkExceptionMacro(<< "Error, Can not write compressed image file for " << m_FileName);
      }

    try
      {


      static const unsigned int maxChunk = ANALYZE_MAXIMUM_IO_CHUNK;

      SizeType bytesRemaining = this->GetImageSizeInBytes();
      while ( bytesRemaining )
        {
        unsigned int bytesToWrite = bytesRemaining > static_cast< SizeType >( maxChunk )
                                    ? maxChunk : static_cast< unsigned int >( bytesRemaining );

        if ( gzwrite(file_p, p, bytesToWrite) != static_cast< int >( bytesToWrite ) )
          {
          itkExceptionMacro(<< "Error, Can not write compressed image file for " << m_FileName);
          }
        p = static_cast< char * >( p ) + bytesToWrite;
        bytesRemaining -= bytesToWrite;
        }
      gzclose(file_p);
      file_p = NULL;
      }
    catch ( ... )
      {

      if ( file_p != NULL )
        {
        gzclose(file_p);
        }
      throw;
      }


    std::string unusedbaseimgname = GetRootName( GetHeaderFileName(m_FileName) );
    unusedbaseimgname += ".img";
    itksys::SystemTools::RemoveFile( unusedbaseimgname.c_str() );
    }
  else
    {

    std::ofstream local_OutputStream;
    local_OutputStream.open(ImageFileName.c_str(), std::ios::out | std::ios::binary);
    if ( !local_OutputStream )
      {
      itkExceptionMacro(<< "Error opening image data file for writing."
                        << m_FileName);
      }
    local_OutputStream.write( (const char *)p, static_cast< std::streamsize >( this->GetImageSizeInBytes() ) );
    bool success = !local_OutputStream.bad();
    local_OutputStream.close();
    if ( !success )
      {
      itkExceptionMacro(<< "Error writing image data."
                        << m_FileName);
      }


    std::string unusedbaseimgname = GetRootName( GetHeaderFileName(m_FileName) );
    unusedbaseimgname += ".img.gz";
    itksys::SystemTools::RemoveFile( unusedbaseimgname.c_str() );
    }
}
