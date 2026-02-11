doQuery( const QString &userFilter )
{
  QString filter = QString( "(&(cn=*)%1(objectClass=kolabGroupOfNames))" ).arg( userFilter );

  QLdapResponse response = Connection::self()->search( QString(), QLdap::Sub, filter , QStringList(), QLatin1String( "cn" ) );

  QString blacklist;
  blacklist.append( "admin" );
  blacklist.append( "maintainer" );

  QLdapEntry::List entries = response.entries();
  QLdapEntry::List filteredEntries;
  for ( int i = 0; i < entries.count(); ++i ) {
    if ( !blacklist.contains( entries[ i ].value( "cn" ) ) )
      filteredEntries.append( entries[ i ] );
  }

  mData.setEntries( filteredEntries );

  emit layoutChanged();
}
