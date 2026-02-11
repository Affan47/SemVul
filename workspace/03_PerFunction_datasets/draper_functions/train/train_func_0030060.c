loadEntry( const QString &id, PagePolicy::State )
{
  QString filter( "objectClass=*" );
  QLdapResponse response = Connection::self()->search( id, QLdap::Base, filter );

  if ( !response.isValid() || response.entries().isEmpty() )
    return Entry();

  return Entry::fromLdapEntry( response.entries().first() );
}
