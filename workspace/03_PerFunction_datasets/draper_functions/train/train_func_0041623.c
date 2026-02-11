IsDirectory( const string &path ) const
{
  struct stat path_stat;
  if ( stat( path.c_str(), &path_stat ) != 0 )
  {
    cerr << "stat() failed on path '" << path << "'." << endl;
    cerr << "Exiting." << endl;
    exit( -1 );
  }

  return ( S_ISDIR( path_stat.st_mode ) );
}
