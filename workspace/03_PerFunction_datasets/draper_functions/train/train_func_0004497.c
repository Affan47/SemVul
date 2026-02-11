splitPathString( const std::string &pathAsString,
                           PathTestNames &testNames )
{
  if ( pathAsString.empty() )
    return true;

  bool isRelative = pathAsString[0] != '/';

  int index = (isRelative ? 0 : 1);
  while ( true )
  {
    int separatorIndex = pathAsString.find( '/', index );
    if ( separatorIndex >= 0 )
    {
      testNames.push_back( pathAsString.substr( index, separatorIndex - index ) );
      index = separatorIndex + 1;
    }
    else
    {
      testNames.push_back( pathAsString.substr( index ) );
      break;
    }
  }

  return isRelative;
}
