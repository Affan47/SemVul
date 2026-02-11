readExclFile( const std::string& file,
  std::vector<std::string>& excls ) const
{
  std::ifstream in( file.c_str() );
  if( !in )
  {
    std::cerr << ExeName << ": Error: Could not open exclusion file "
              << file << ". Aborting." << std::endl;
    return false;
  }

  char buffer[1024];

  while( in.getline( buffer, sizeof( buffer ) ) )
  {
    std::string line = buffer;
    trimString( line );
    if( line.length() > 0 )
      excls.push_back( line );
  }

  in.close();

  return true;
}
