may_access_filename( const char * const name )
  {
  if( restricted_ &&
      ( *name == '!' || !strcmp( name, ".." ) || strchr( name, '/' ) ) )
    {
    set_error_msg( "Shell access restricted" );
    return false;
    }
  return true;
  }
