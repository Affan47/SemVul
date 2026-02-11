get( const char *key, char *&text, const char *defaultValue )
{
  const char *v = node->get( key );
  if ( v && strchr( v, '\\' ) )
  {
    text = decodeText( v );
    return 1;
  }
  if ( !v ) v = defaultValue;
  if ( v )
    text = strdup( v );
  else
    text = 0;
  return ( v != defaultValue );
}
