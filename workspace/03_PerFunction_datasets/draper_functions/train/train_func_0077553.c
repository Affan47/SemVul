read()
{
    while( !m_xml.atEnd() && !m_xml.hasError() )
    {
        m_xml.readNext();
        if( m_xml.isStartElement() && m_xml.name() == "event" )
        {
            QHash<QString, QString> artists;
            LastFmEventPtr event( new LastFmEvent );
            while( !m_xml.atEnd() )
            {
                m_xml.readNext();
                const QStringRef &n = m_xml.name();
                if( m_xml.isEndElement() && n == "event" )
                    break;

                if( m_xml.isStartElement() )
                {
                    const QXmlStreamAttributes &a = m_xml.attributes();
                    if( n == "title" )
                        event->setName( m_xml.readElementText() );
                    else if( n == "artists" )
                        artists = readEventArtists();
                    else if( n == "venue" )
                    {
                        LastFmVenueXmlParser venueParser( m_xml );
                        if( venueParser.read() )
                            event->setVenue( venueParser.venue() );
                    }
                    else if( n == "startDate" )
                        event->setDate( KDateTime::fromString( m_xml.readElementText(), "%a, %d %b %Y %H:%M:%S" ) );
                    else if( n == "image" && a.hasAttribute("size") )
                        event->setImageUrl( LastFmEvent::stringToImageSize(a.value("size").toString()), KUrl( m_xml.readElementText() ) );
                    else if( n == "url" )
                        event->setUrl( KUrl( m_xml.readElementText() ) );
                    else if( n == "attendance" )
                        event->setAttendance( m_xml.readElementText().toInt() );
                    else if( n == "cancelled" )
                        event->setCancelled( bool( m_xml.readElementText().toInt() ) );
                    else if( n == "tags" )
                        event->setTags( readEventTags() );
                    else
                        m_xml.skipCurrentElement();
                }
            }
            event->setHeadliner( artists.value("headliner") );
            event->setParticipants( artists.values("artist") );
            m_events << event;
        }
    }
    return !m_xml.error();
}
