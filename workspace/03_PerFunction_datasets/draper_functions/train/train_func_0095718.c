doQuery( const QString &userFilter )
{
  QString memberBase( "cn=maintainer,cn=internal," + Connection::self()->baseDn() );
  QString memberFilter( "(objectClass=kolabGroupOfNames)" );
  QLdapResponse memberResponse = Connection::self()->search( memberBase, QLdap::Sub, memberFilter );

  if ( !memberResponse.entries().isEmpty() ) {

    QStringList members = memberResponse.entries().first().values( "member" );

    QLdapEntry::List adminEntries;

    QString blacklist;
    blacklist.append( "manager" );


    QString filter = QString( "(&(cn=*)%1(objectClass=inetOrgPerson)(uid=*)(sn=*))" ).arg( userFilter );
    QLdapResponse response = Connection::self()->search( "", QLdap::Sub, filter, QStringList(), QLatin1String( "cn" ) );
    QLdapEntry::List entries = response.entries();
    for ( int i = 0; i < entries.count(); ++i ) {
      if ( members.contains( entries[ i ].dn() ) &&
           !blacklist.contains( entries[ i ].value( "cn" ) ) ) {
        adminEntries.append( entries[ i ] );
      }
    }

    mData.setEntries( adminEntries );
  }

  emit layoutChanged();
}
