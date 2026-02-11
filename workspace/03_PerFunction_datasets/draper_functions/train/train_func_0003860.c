findOrCreate( const QString & path )
{

    if ( path.isEmpty() || path == QLatin1String("/") || path == QLatin1String(".") )
    {

        return rootDir();
    }


    const KArchiveEntry* ent = rootDir()->entry( path );
    if ( ent )
    {
        if ( ent->isDirectory() )

            return (KArchiveDirectory *) ent;
        else
            kWarning() << "Found" << path << "but it's not a directory";
    }


    int pos = path.lastIndexOf( QLatin1Char('/') );
    KArchiveDirectory * parent;
    QString dirname;
    if ( pos == -1 )
    {
        parent =  rootDir();
        dirname = path;
    }
    else
    {
        QString left = path.left( pos );
        dirname = path.mid( pos + 1 );
        parent = findOrCreate( left );
    }


    KArchiveDirectory * e = new KArchiveDirectory( this, dirname, d->rootDir->permissions(),
                                                   d->rootDir->date(), d->rootDir->user(),
                                                   d->rootDir->group(), QString() );
    parent->addEntry( e );
    return e;
}
