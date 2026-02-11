loadEntry( const QString &id, PagePolicy::State )
{
  QString filter( "objectClass=*" );
  QLdapResponse response = Connection::self()->search( id, QLdap::Base, filter );

  if ( !response.isValid() || response.entries().isEmpty() )
    return Entry();

  Entry entry = Entry::fromLdapEntry( response.entries().first() );

  QStringList dnParts = entry.id().split( "," );
  if ( dnParts.contains( "cn=internal" ) )
    entry.setValue( "hidden", "TRUE" );
  else
    entry.setValue( "hidden", "FALSE" );

  return entry;
}
