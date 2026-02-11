loadGame( const KUrl & url, bool addToRecentFiles )
{
    QString fileName;
    if( !KIO::NetAccess::download( url, fileName, this ) )
    {
        KMessageBox::error( this, i18n("Downloading file failed.") );
        return false;
    }
    QFile file( fileName );

    if ( !file.open( QIODevice::ReadOnly ) )
    {
        KMessageBox::error( this, i18n("Opening file failed.") );
        KIO::NetAccess::removeTempFile( fileName );
        return false;
    }

    QXmlStreamReader xml( &file );
    if ( !xml.readNextStartElement() )
    {
        KMessageBox::error( this, i18n("Error reading XML file: ") + xml.errorString() );
        KIO::NetAccess::removeTempFile( fileName );
        return false;
    }

    int gameId = -1;
    bool isLegacyFile;

    if ( xml.name() == "dealer" )
    {
        isLegacyFile = true;
        bool ok;
        int id = xml.attributes().value("id").toString().toInt( &ok );
        if ( ok )
            gameId = id;
    }
    else if ( xml.name() == "kpat-game" )
    {
        isLegacyFile = false;
        QStringRef gameType = xml.attributes().value("game-type");
        foreach ( const DealerInfo * di, DealerInfoList::self()->games() )
        {
            if ( di->baseIdString() == gameType )
            {
                gameId = di->baseId();
                break;
            }
        }
    }
    else
    {
        KMessageBox::error( this, i18n("XML file is not a KPat save.") );
        KIO::NetAccess::removeTempFile( fileName );
        return false;
    }

    if ( !m_dealer_map.contains( gameId ) )
    {
        KMessageBox::error( this, i18n("Unrecognized game id.") );
        KIO::NetAccess::removeTempFile( fileName );
        return false;
    }


    if ( m_dealer && !m_dealer->allowedToStartNewGame() )
    {
        KIO::NetAccess::removeTempFile( fileName );
        return false;
    }

    setGameType( gameId );

    xml.clear();
    file.reset();

    bool success = isLegacyFile ? m_dealer->loadLegacyFile( &file )
                                : m_dealer->loadFile( &file );

    file.close();
    KIO::NetAccess::removeTempFile( fileName );

    if ( !success )
    {
        KMessageBox::error( this, i18n("Errors encountered while parsing file.") );
        slotShowGameSelectionScreen();
        return false;
    }

    setGameCaption();

    if ( addToRecentFiles )
        m_recentFilesAction->addUrl( url );

    return true;
}
