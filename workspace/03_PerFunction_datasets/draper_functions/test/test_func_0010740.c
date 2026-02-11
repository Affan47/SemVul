catalogLocaleDir( const QString &name,
                                    const QString &language )
{
  QString relpath =  QString::fromLatin1( "%1/LC_MESSAGES/%2.mo" )
                    .arg( language ).arg( name );
  return KGlobal::dirs()->findResourceDir( "locale", relpath );
}
