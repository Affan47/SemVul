BuildLUT( Bitmap & bitmap, unsigned int maxcolor )
{
  assert( Internals->ConvertRGBToPaletteColor );
  using namespace quantization;
  const unsigned int *dims = bitmap.GetDimensions();
  unsigned int numPoints = dims[0]*dims[1];

  std::vector<unsigned char> indeximage;
  std::list<Point> palette =
    medianCut(bitmap.GetDataElement(), numPoints, maxcolor, indeximage);

  size_t ncolors = palette.size();
  LookupTable & lut = bitmap.GetLUT();
  lut.Clear();
  lut.Allocate( 8 );
  std::vector< unsigned char > buffer[3];
  for( int i = 0; i < 3; ++i )
    buffer[i].reserve( ncolors );

  std::list<Point>::const_iterator it = palette.begin();
  for( ; it != palette.end(); ++it )
    {
    Point const & p = *it;
    for( int i = 0; i < 3; ++i )
      buffer[i].push_back( p.x[i] );
    }

  for( int i = 0; i < 3; ++i )
    {
    lut.InitializeLUT( LookupTable::LookupTableType(i), (unsigned short)ncolors, 0, 8 );
    lut.SetLUT( LookupTable::LookupTableType(i), &buffer[i][0], (unsigned short)ncolors );
    }

  bitmap.GetDataElement().SetByteValue( (char*)&indeximage[0], (uint32_t)indeximage.size() );
  assert( lut.Initialized() );
}
