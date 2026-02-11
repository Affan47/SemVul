parseRelease( const QDomElement &e )
{
    QString id;
    QVariantMap release;

    if( e.hasAttribute( "id" ) )
        id = e.attribute( "id" );
    if( id.isEmpty() )
        return id;

    if( releases.contains( id ) )
        release = releases.value( id );
    else
        release.insert( MusicBrainz::RELEASEID, id );
    if( release.isEmpty() )
        return id;

    QDomNode dNode = e.firstChild();
    QDomElement dElement;
    QString elementName;

    while( !dNode.isNull() )
    {
        if( dNode.isElement() )
        {
            dElement = dNode.toElement();
            elementName = dElement.tagName();

            if( elementName == "title" )


                release.insert( Meta::Field::TITLE, dElement.text() );
            else if( elementName == "medium-list" )
            {
                QVariantMap info = parseMediumList( dElement );
                QVariantList trackCountList = info.values( MusicBrainz::TRACKCOUNT );
                int trackCount = 0;
                foreach( const QVariant &count, trackCountList )
                {
                    trackCount += count.toInt();
                    if( count.toInt() > 0 )
                        release.insert( MusicBrainz::TRACKCOUNT, count.toInt() );
                }
                if( info.contains( Meta::Field::DISCNUMBER ) )
                {
                    int discNumber = info.value( Meta::Field::DISCNUMBER ).toInt();
                    if( discNumber < 1 || ( discNumber == 1 &&
                        ( trackCount <= 0 || trackCountList.size() != 2 ) ) )
                        info.remove( Meta::Field::DISCNUMBER );
                }
                QVariantList trackInfoList = m_currentTrackInfo.value( id ).toList();
                trackInfoList.append( info );
                m_currentTrackInfo.insert( id, trackInfoList );
            }
            else if( elementName == "release-group" )
                release.insert( MusicBrainz::RELEASEGROUPID, parseReleaseGroup( dElement ) );
        }
        dNode = dNode.nextSibling();
    }

    releases.insert( id, release );
    return id;
}
