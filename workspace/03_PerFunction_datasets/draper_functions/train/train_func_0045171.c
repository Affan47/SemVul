updateDragData( const TrackInfo& track )
{

    QHash<QString, QString> data;
    data.insert( "artist", track.artist() );
    data.insert( "album", track.album() );
    data.insert( "track", track.track() );

    ui.artistPic->setItemData( data );
    ui.albumPic->setItemData( data );

    ui.artistLabel->setItemData( 0, data );
    ui.aboutLabel->setItemData( 0, data );
    ui.albumLabel->setItemData( 0, data );
    ui.trackLabel->setItemData( 0, data );
}
