readImage24( QImage &img, QDataStream &s, const PCXHEADER &header )
{
  QByteArray r_buf( header.BytesPerLine, 0 );
  QByteArray g_buf( header.BytesPerLine, 0 );
  QByteArray b_buf( header.BytesPerLine, 0 );

  img = QImage( header.width(), header.height(), QImage::Format_RGB32 );

  for ( int y=0; y<header.height(); ++y )
  {
    if ( s.atEnd() )
    {
      img = QImage();
      return;
    }

    readLine( s, r_buf, header );
    readLine( s, g_buf, header );
    readLine( s, b_buf, header );

    uint *p = ( uint * )img.scanLine( y );
    for ( int x=0; x<header.width(); ++x )
      p[ x ] = qRgb( r_buf[ x ], g_buf[ x ], b_buf[ x ] );
  }
}
