TryJPEGLSCodec(const DataElement &pixelde, Bitmap const &input, Bitmap &output)
{
  unsigned long len = input.GetBufferLength(); (void)len;

  const TransferSyntax &ts = GetTransferSyntax();

  JPEGLSCodec codec;
  if( codec.CanCode( ts ) )
    {
    codec.SetDimensions( input.GetDimensions() );
    codec.SetPixelFormat( input.GetPixelFormat() );

    codec.SetPlanarConfiguration( input.GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( input.GetPhotometricInterpretation() );
    codec.SetNeedOverlayCleanup( input.AreOverlaysInPixelData() );
    DataElement out;

    bool r = codec.Code(pixelde, out);
    if(!r) return false;
    output.SetPlanarConfiguration( 0 );

    DataElement &de = output.GetDataElement();
    de.SetValue( out.GetValue() );
    UpdatePhotometricInterpretation( input, output );
    return r;
    }
  return false;
}
