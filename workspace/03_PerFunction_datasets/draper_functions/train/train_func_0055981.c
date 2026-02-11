append_path_delim( string &path ) {
  if ( path.at( path.length() - 1 ) != PATHDELIM ) path += PATHDELIM;
}
