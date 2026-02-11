applyWhitespaceOnly( wstring const & in )
{
  wchar const * nextChar = in.data();

  wstring out;

  out.reserve( in.size() );

  for( size_t left = in.size(); left--; ++nextChar )
    if ( !isWhitespace( *nextChar ) )
      out.push_back( *nextChar );

  return out;
}
