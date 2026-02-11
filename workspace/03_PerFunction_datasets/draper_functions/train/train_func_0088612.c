open( QIODevice::OpenMode mode )
{
    Q_ASSERT( mode != QIODevice::NotOpen );

    if ( isOpen() )
        close();

    if ( !d->fileName.isEmpty() )
    {
        Q_ASSERT( !d->dev );
        if ( !createDevice( mode ) )
            return false;
    }

    Q_ASSERT( d->dev );

    if ( !d->dev->isOpen() && !d->dev->open( mode ) )
        return false;

    d->mode = mode;

    Q_ASSERT( !d->rootDir );
    d->rootDir = 0;

    return openArchive( mode );
}
