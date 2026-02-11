run()
{
    DEBUG_BLOCK
    debug() << "file:" << m_databaseLocation;
    QScopedPointer<QFile> file( new QFile( m_databaseLocation ) );
    if( !file->exists() )
    {
        debug() << "COULDN'T FIND DB FILE!";
        emit importError( "" );
        m_failed = true;
        return;
    }
    if ( !file->open( QIODevice::ReadOnly ) )
    {
        debug() << "COULDN'T OPEN DB FILE!";
        emit importError( "" );
        m_failed = true;
        return;
    }
    setDevice( file.data() );


    while( !atEnd() )
    {
        if( m_aborted )
            return;

        readNext();

        if ( name() == "key" && readElementText() == "Tracks" )
        {
            readNext();
            readNext();
            readNext();
            debug() << "got start of tracks";
            while( !atEnd() && !( isEndElement() && name() == "dict" ) )
            {
                if( m_aborted )
                    return;


                if( isStartElement() && name() == "dict")
                {
                    readTrackElement();
                }
                readNext();
            }
        }
    }

    if( m_tracksForInsert.size() > 0 )
    {
        Collections::CollectionLocation *location = CollectionManager::instance()->primaryCollection()->location();

        QMapIterator<Meta::TrackPtr, QString> j(m_tracksForInsert);
        while (j.hasNext()) {
            j.next();
            location->insert( j.key(), j.value() );
        }
    }

    debug() << "done importing xml file";
}
