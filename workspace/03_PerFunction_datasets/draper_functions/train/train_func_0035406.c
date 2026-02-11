Write(const char *filename, const DataElement &out) const
{
  std::ofstream os(filename, std::ios::binary);
  const unsigned int *dims = this->GetDimensions();
  const PhotometricInterpretation &pi = this->GetPhotometricInterpretation();
  if( pi == PhotometricInterpretation::MONOCHROME2
    || pi == PhotometricInterpretation::MONOCHROME1 )
    {
    os << "P5\n";
    }
  else if( pi == PhotometricInterpretation::RGB
    || pi == PhotometricInterpretation::PALETTE_COLOR )
    {
    os << "P6\n";
    }
  else
    {
    gdcmErrorMacro( "PhotometricInterpretation unhandled: " << pi );
    return false;
    }
  os << dims[0] << " " << dims[1] << "\n";

  const unsigned int pc = this->GetPlanarConfiguration();
  if( pc )
    {
    gdcmErrorMacro( "PlanarConfiguration unhandled: " << pc );
    return false;
    }

  const PixelFormat& pf = GetPixelFormat();
  switch(pf)
    {
  case PixelFormat::UINT8:

    os << "255";
    break;
  case PixelFormat::UINT16:

    os << "65535";
    break;
  default:
    gdcmErrorMacro( "Unhandled PF: " << pf );
    return false;
    }
  os << "\n";

  const ByteValue *bv = out.GetByteValue();

  if(!bv)
    {
    gdcmErrorMacro( "PNM Codec does not handle compress syntax. You need to decompress first." );
    return false;
    }
  assert(bv);

  if( pi == PhotometricInterpretation::PALETTE_COLOR )
    {
    std::stringstream is;
    is.write( bv->GetPointer(), bv->GetLength() );

    const LookupTable &lut = this->GetLUT();
    lut.Decode(is, os);
    }
  else
    {
    if( pf.GetBitsAllocated() == 16 )
      {
      bv->Write<SwapperDoOp, uint16_t>( os );
      }
    else
      {

      bv->WriteBuffer( os );
      }
    }

  os.close();


  return true;
}
