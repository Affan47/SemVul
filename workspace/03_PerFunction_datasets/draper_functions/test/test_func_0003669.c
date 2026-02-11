entry( const QString& _name ) const
{
    QString name = QDir::cleanPath(_name);
    int pos = name.indexOf( QLatin1Char('/') );
  if ( pos == 0 )
  {
    if (name.length()>1)
    {
      name = name.mid( 1 );
      pos = name.indexOf( QLatin1Char('/') );
    }
    else
      return this;
  }

  if ( pos != -1 && pos == name.length()-1 )
  {
    name = name.left( pos );
    pos = name.indexOf( QLatin1Char('/') );
  }
  if ( pos != -1 )
  {
    const QString left = name.left(pos);
    const QString right = name.mid(pos + 1);


    const KArchiveEntry* e = d->entries.value( left );
    if ( !e || !e->isDirectory() )
      return 0;
    return static_cast<const KArchiveDirectory*>(e)->entry( right );
  }

  return d->entries.value( name );
}
