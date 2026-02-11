numberOfMails( QLdap* connection, const QString &baseDn, const QString &email, const QStringList &excludedDns )
{


  const QString filter = QString( "(|(mail=%1)(alias=%2)(uid=%3))" ).arg( email, email, email );
  const QStringList attributes( "dn" );

  const QLdapResponse response = connection->search( baseDn, QLdap::Sub, filter, attributes );

  int count = 0;

  const QLdapEntry::List entries = response.entries();
  if ( !excludedDns.isEmpty() ) {
    for ( int i = 0; i < entries.count(); ++i ) {
      if ( excludedDns.contains( entries[ i ].dn() ) )
        continue;

      count++;
    }
  } else
    count += entries.count();

  return count;
}
