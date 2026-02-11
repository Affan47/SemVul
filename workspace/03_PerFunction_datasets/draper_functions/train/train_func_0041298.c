ComputeMOSAICDimensions( unsigned int dims[3] )
{
  CSAHeader csa;
  DataSet& ds = GetFile().GetDataSet();

  const PrivateTag &t1 = csa.GetCSAImageHeaderInfoTag();
  int numberOfImagesInMosaic = 0;
  if( csa.LoadFromDataElement( ds.GetDataElement( t1 ) ) )
  {

    if( csa.FindCSAElementByName( "NumberOfImagesInMosaic" ) )
    {
      const CSAElement &csael4 = csa.GetCSAElementByName( "NumberOfImagesInMosaic" );
      if( !csael4.IsEmpty() )
      {
        Element<VR::IS, VM::VM1> el4 = {{ 0 }};
        el4.Set( csael4.GetValue() );
        numberOfImagesInMosaic = el4.GetValue();
      }
    }
  }
  else
  {


    PrivateTag t2 (0x0019,0x0a, "SIEMENS MR HEADER");
    const DataElement &de = ds.GetDataElement( t2 );
    const ByteValue * bv = de.GetByteValue();
    if( bv )
    {
      Element<VR::US, VM::VM1> el1 = {{0}};
      std::istringstream is;
      is.str( std::string( bv->GetPointer(), bv->GetLength() ) );
      el1.Read( is );
      numberOfImagesInMosaic = el1.GetValue();
    }
  }
  if( !numberOfImagesInMosaic )
  {
    gdcmErrorMacro( "Could not find NumberOfImagesInMosaic" );
    return false;
  }

  std::vector<unsigned int> colrow =
    ImageHelper::GetDimensionsValue( GetFile() );
  dims[0] = colrow[0];
  dims[1] = colrow[1];

  const unsigned int div = (unsigned int )ceil(sqrt( (double)numberOfImagesInMosaic ) );
  dims[0] /= div;
  dims[1] /= div;
  dims[2] = numberOfImagesInMosaic;
  return true;
}
