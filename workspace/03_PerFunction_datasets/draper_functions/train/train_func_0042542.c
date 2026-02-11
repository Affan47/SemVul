sync ( void )
{
  if( !SyncCacheViewPixels( _view, &_exception ) )
    throwException( _exception );
}
