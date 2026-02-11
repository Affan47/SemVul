OpenFileForWriting(std::ofstream & outputStream, const std::string & filename,
                                     bool truncate, bool ascii)
{

  if ( filename.empty() )
    {
    itkExceptionMacro( << "A FileName must be specified." );
    }


  if ( outputStream.is_open() )
    {
    outputStream.close();
    }


  itkDebugMacro( << "Opening file for writing: " << filename );

  std::ios::openmode mode = std::ios::out;
  if ( truncate )
    {

    mode |= std::ios::trunc;
    }
  else
    {
    mode |= std::ios::in;

    if ( !itksys::SystemTools::FileExists( filename.c_str() ) )
      {
      itksys::SystemTools::Touch( filename.c_str(), true );


      }
    }
  if ( !ascii )
    {
    mode |= std::ios::binary;
    }

  outputStream.open( filename.c_str(), mode );

  if ( !outputStream.is_open() || outputStream.fail() )
    {
    itkExceptionMacro( << "Could not open file: "
                       << filename << " for writing."
                       << std::endl
                       << "Reason: "
                       << itksys::SystemTools::GetLastSystemError() );
    }
}
