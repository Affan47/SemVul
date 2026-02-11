vtkLSTrimWhitespace( std::string& line )
{
  std::string::size_type llen = line.length();
  while ( llen &&
    ( line[llen - 1] == ' ' ||
      line[llen - 1] == '\t' ||
      line[llen - 1] == '\r' ||
      line[llen - 1] == '\n' ) )
    {
    --llen;
    }

  std::string::size_type nameStart = 0;
  while ( nameStart < llen &&
    ( line[nameStart] == ' ' ||
      line[nameStart] == '\t' ) )
    {
    ++nameStart;
    }

  line = line.substr( nameStart, llen - nameStart );
}
