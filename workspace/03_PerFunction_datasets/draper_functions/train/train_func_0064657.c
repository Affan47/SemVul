Save( MemBuffer &file ) const {
  file.Write8( type );
  for ( int i = 0; i < 4; ++i ) file.Write16( data[i] );
  return 0;
}
