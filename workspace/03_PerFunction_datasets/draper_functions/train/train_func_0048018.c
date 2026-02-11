Split( const std::string& s, std::string& lpart, std::string& rpart, const std::string& delims )
{
  std::string::size_type pos = s.find_first_of( delims );
  if ( pos != std::string::npos )
    {
    lpart = s.substr( 0, pos );
    StringTools::Trim( lpart );
    rpart = s.substr( pos + 1 );
    StringTools::Trim( rpart );
    }
  else
    {
    lpart = s;
    StringTools::Trim( lpart );
    rpart = "";
    }
}
