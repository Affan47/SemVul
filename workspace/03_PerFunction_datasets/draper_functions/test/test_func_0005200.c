guessMetadata( const Meta::TrackPtr &track ) const
{
    DEBUG_BLOCK
    debug() << "Trying to guess metadata from filename:" << track->playableUrl().fileName();
    QVariantMap metadata;

    if( ( track->artist().isNull() || track->artist()->name().isEmpty() ) &&
        ( track->album().isNull() || track->album()->name().isEmpty() ) )
    {
        Meta::FieldHash tags = Meta::Tag::TagGuesser::guessTags( track->playableUrl().fileName() );
        foreach( const quint64 &key, tags.keys() )
        {
            switch( key )
            {
            case Meta::valAlbum:
                metadata.insert( Meta::Field::ALBUM, tags[key] );
                break;
            case Meta::valAlbumArtist:
                metadata.insert( Meta::Field::ALBUMARTIST, tags[key] );
                break;
            case Meta::valArtist:
                metadata.insert( Meta::Field::ARTIST, tags[key] );
                break;
            case Meta::valDiscNr:
                metadata.insert( Meta::Field::DISCNUMBER, tags[key] );
                break;
            case Meta::valTitle:
                metadata.insert( Meta::Field::TITLE, tags[key] );
                break;
            case Meta::valTrackNr:
                metadata.insert( Meta::Field::TRACKNUMBER, tags[key] );
                break;
            }
        }
    }
    else
        metadata.insert( Meta::Field::TITLE, track->name() );

    if( !track->album().isNull() && !track->album()->name().isEmpty() )
        metadata.insert( Meta::Field::ALBUM, track->album()->name() );
    if( !track->artist().isNull() && !track->artist()->name().isEmpty() )
        metadata.insert( Meta::Field::ARTIST, track->artist()->name() );
    if( track->discNumber() > 0 )
        metadata.insert( Meta::Field::DISCNUMBER, track->discNumber() );
    if( track->trackNumber() > 0 )
        metadata.insert( Meta::Field::TRACKNUMBER, track->trackNumber() );

    debug() << "Guessed track info:";
    foreach( const QString &tag, metadata.keys() )
        debug() << '\t' << tag << ":\t" << metadata.value( tag ).toString();

    return metadata;
}
