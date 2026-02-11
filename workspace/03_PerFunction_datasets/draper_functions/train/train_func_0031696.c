Write()
{
  if( !PrepareWrite() ) return false;

  assert( Stream );
  if( !Writer::Write() )
    {
    return false;
    }
  return true;
}
