GetActualNumberOfSplitsForWriting(unsigned int numberOfRequestedSplits,
                                               const ImageIORegion & pasteRegion,
                                               const ImageIORegion & largestPossibleRegion)
{
  if ( this->GetUseCompression() )
    {

    if ( pasteRegion != largestPossibleRegion )
      {
      itkExceptionMacro( "Pasting and compression is not supported! Can't write:" << this->GetFileName() );
      }
    else if ( numberOfRequestedSplits != 1 )
      {
      itkDebugMacro("Requested streaming and compression");
      itkDebugMacro("Meta IO is not streaming now!");
      }
    return 1;
    }

  if ( !itksys::SystemTools::FileExists( m_FileName.c_str() ) )
    {

    }
  else if ( pasteRegion != largestPossibleRegion )
    {


    std::string errorMessage;
    Pointer     headerImageIOReader = Self::New();

    try
      {
      headerImageIOReader->SetFileName( m_FileName.c_str() );
      headerImageIOReader->ReadImageInformation();
      }
    catch ( ... )
      {
      errorMessage = "Unable to read information from file: " + m_FileName;
      }


    if ( errorMessage.size() )
      {

      }

    else if ( headerImageIOReader->m_MetaImage.CompressedData() )
      {
      errorMessage = "File is compressed: " + m_FileName;
      }


    else if ( headerImageIOReader->GetNumberOfComponents() != this->GetNumberOfComponents()
              || headerImageIOReader->GetComponentType() != this->GetComponentType() )
      {
      errorMessage = "Component type does not match in file: " + m_FileName;
      }

    else if ( headerImageIOReader->GetNumberOfDimensions() != this->GetNumberOfDimensions() )
      {
      errorMessage = "Dimensions does not match in file: " + m_FileName;
      }
    else
      {
      for ( unsigned int i = 0; i < this->GetNumberOfDimensions(); ++i )
        {

        if ( headerImageIOReader->GetDimensions(i) != this->GetDimensions(i)
             || headerImageIOReader->GetSpacing(i) != this->GetSpacing(i)
             || headerImageIOReader->GetOrigin(i) != this->GetOrigin(i) )
          {
          errorMessage = "Size, spacing or origin does not match in file: " + m_FileName;
          break;
          }

        if ( headerImageIOReader->GetDirection(i) != this->GetDirection(i) )
          {
          errorMessage = "Direction cosines does not match in file: " + m_FileName;
          break;
          }
        }
      }

    if ( errorMessage.size() )
      {
      itkExceptionMacro("Unable to paste because pasting file exists and is different. " << errorMessage);
      }
    else if ( headerImageIOReader->GetPixelType() != this->GetPixelType() )
      {


      itkWarningMacro("Pixel types does not match file, but component type and number of components do.");
      }
    }
  else if ( numberOfRequestedSplits != 1 )
    {


    if ( !itksys::SystemTools::RemoveFile( m_FileName.c_str() ) )
      {
      itkExceptionMacro("Unable to remove file for streaming: " << m_FileName);
      }
    }

  return GetActualNumberOfSplitsForWritingCanStreamWrite(numberOfRequestedSplits, pasteRegion);
}
