indexOf( DirEntry* e )
{
  for( unsigned i = 0; i < entryCount(); i++ )
    if( entry( i ) == e ) return i;

  return -1;
}
