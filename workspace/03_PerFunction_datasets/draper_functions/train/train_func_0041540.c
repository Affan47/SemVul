isCuFile( const std::string& file )
{
  return
    ( file.length() >= 3 && file.compare( file.length() - 3, 3, ".cu" ) == 0 );
}
