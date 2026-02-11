TrimLeft( std::string& str, const std::string& dislike )
{
  if ( !str.empty() )
    {
    std::string::size_type pos = str.find_first_not_of( dislike );
    if ( pos != std::string::npos )
      {
      if ( pos > 0 )
        {
        str.erase( 0, pos );
        }
      }
    else
      {
      str.clear();
      }
    }

  return str;
}
