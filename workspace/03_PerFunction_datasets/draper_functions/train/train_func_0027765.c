parseScannerOutput()
{

    while( !m_reader.atEnd() )
    {

        {
            QMutexLocker locker( &m_mutex );
            if( m_abortRequested )
                return false;
        }

        m_reader.readNext();
        if( m_reader.hasError() )
        {
            return false;
        }
        else if( m_reader.isStartElement() )
        {
            QStringRef name = m_reader.name();
            if( name == "scanner" )
            {
                int totalCount = m_reader.attributes().value( "count" ).toString().toInt();
                emit directoryCount( totalCount );
            }
            else if( name == "directory" )
            {
                QSharedPointer<CollectionScanner::Directory> dir( new CollectionScanner::Directory( &m_reader ) );
                emit directoryScanned( dir );
            }
            else
            {
                warning() << "Unexpected xml start element"<<name<<"in input";
                m_reader.skipCurrentElement();
            }

        }
        else if( m_reader.isEndElement() )
        {
            if( m_reader.name() == "scanner" )
                return true;
        }
        else if( m_reader.isEndDocument() )
        {
            return true;
        }
    }

    return false;
}
