applyFullCaseOnly( wstring const & in )
{
  wstring caseFolded;

  caseFolded.reserve( in.size() * foldCaseMaxOut );

  wchar const * nextChar = in.data();

  wchar buf[ foldCaseMaxOut ];

  for( size_t left = in.size(); left--; )
    caseFolded.append( buf, foldCase(  *nextChar++, buf ) );

  return caseFolded;
}
