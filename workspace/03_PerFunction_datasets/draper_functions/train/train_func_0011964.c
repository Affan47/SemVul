add_type( const String& name, const String& type, const ftype32& scale )
{
  int i, j;
  for ( j = 0; j < 200; j++ )
    if ( names[j][0] == '\0' ) break;
  if ( j == 200 )
    Message::message( Message_fatal( "CCP4MTZ_type_registry: registry full." ) );
  for ( i = 0; i < Util::min( int(name.length()), 11 ); i++ )
    names[j][i] = name[i];
  names[j][i] = '\0';
  for ( i = 0; i < Util::min( int(type.length()), 3 ); i++ )
    types[j][i] = type[i];
  types[j][i] = '\0';
  scales[j] = scale;
}
