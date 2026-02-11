PixelRepresentationCallback( DICOMParser *parser,
                                                  doublebyte,
                                                  doublebyte,
                                                  DICOMParser::VRTypes,
                                                  unsigned char* val,
                                                  quadbyte len)
{
  unsigned short uival = 1;

  if (len > 0)
    {
    uival = DICOMFile::ReturnAsUnsignedShort(val, parser->GetDICOMFile()->GetPlatformIsBigEndian());
    }

#ifdef DEBUG_DICOM_APP_HELPER
  dicom_stream::cout << "Pixel Representation: " << (uival ? "Signed" : "Unsigned") << dicom_stream::endl;
#endif
  this->PixelRepresentation = uival;
}
