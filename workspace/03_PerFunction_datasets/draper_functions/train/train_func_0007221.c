find_filename_ext( const char *filename )
{
  char *extension = NULL;


  if( filename ) {
    extension = strrchr( filename, '.' ); if( extension ) extension++;
  }
  return extension;
}
