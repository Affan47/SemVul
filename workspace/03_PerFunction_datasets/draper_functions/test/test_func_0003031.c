writeImage8( QImage &img, QDataStream &s, PCXHEADER &header )
{
  header.Bpp = 8;
  header.NPlanes = 1;
  header.BytesPerLine = img.bytesPerLine();

  s << header;

  QByteArray buf( header.BytesPerLine, 0 );

  for ( int y=0; y<header.height(); ++y )
  {
    quint8 *p = img.scanLine( y );

    for ( int i=0; i<header.BytesPerLine; ++i )
      buf[ i ] = p[ i ];

    writeLine( s, buf );
  }


  quint8 byte = 12;
  s << byte;


  for ( int i=0; i<256; ++i )
    s << RGB::from( img.color( i ) );
}
