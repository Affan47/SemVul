TryJPEG2000Codec(const DataElement &pixelde, Bitmap const &input, Bitmap &output)
{
  unsigned long len = input.GetBufferLength(); (void)len;

  const TransferSyntax &ts = GetTransferSyntax();

  JPEG2000Codec j2kcodec;
  ImageCodec *codec = &j2kcodec;
  if( UserCodec && UserCodec->CanCode( ts ) )
    {
    codec = UserCodec;
    }

  if( codec->CanCode( ts ) )
    {
    codec->SetDimensions( input.GetDimensions() );
    codec->SetPixelFormat( input.GetPixelFormat() );
    codec->SetNumberOfDimensions( input.GetNumberOfDimensions() );
    codec->SetPlanarConfiguration( input.GetPlanarConfiguration() );
    codec->SetPhotometricInterpretation( input.GetPhotometricInterpretation() );
    codec->SetNeedOverlayCleanup( input.AreOverlaysInPixelData() );
    DataElement out;

    bool r = codec->Code(pixelde, out);


    output.SetPlanarConfiguration( 0 );

    if( input.GetPixelFormat().GetSamplesPerPixel() == 3 )
      {
      if( input.GetPhotometricInterpretation().IsSameColorSpace( PhotometricInterpretation::RGB ) )
        {
        if( ts == TransferSyntax::JPEG2000Lossless )
          {
          output.SetPhotometricInterpretation( PhotometricInterpretation::YBR_RCT );
          }
        else
          {
          assert( ts == TransferSyntax::JPEG2000 );
          output.SetPhotometricInterpretation( PhotometricInterpretation::YBR_ICT );
          }
        }
      else
        {
        assert( input.GetPhotometricInterpretation().IsSameColorSpace( PhotometricInterpretation::YBR_FULL ) );
        if( ts == TransferSyntax::JPEG2000Lossless )
          {
          output.SetPhotometricInterpretation( PhotometricInterpretation::YBR_FULL );

          gdcmWarningMacro( "Technically this is not defined in the standard. \n"
            "Some validator may complains this image is invalid, but would be wrong.");
          }
        else
          {
          assert( ts == TransferSyntax::JPEG2000 );


          output.SetPhotometricInterpretation( PhotometricInterpretation::YBR_FULL );
          }
        }
      }
    else
      {
      assert( input.GetPixelFormat().GetSamplesPerPixel() == 1 );
      }

    if( !r ) return false;
    DataElement &de = output.GetDataElement();
    de.SetValue( out.GetValue() );
    UpdatePhotometricInterpretation( input, output );
    return r;
    }
  return false;
}
