TestForSeparator()
{
  if( mIsBinaryFormat)
    return;

  FindNextNoneWhiteSpace();
  if( P >= End)
    return;


  if( *P == ';' || *P == ',')
    P++;
}
