openTrackPage() const
{
    QModelIndex index = selectedIndexes().first();
    if( !index.isValid() || !index.internalPointer() )
        return;

    QString trackID = index.data( MusicBrainzTagsModel::TracksRole ).toStringList().first();
    if( trackID.isEmpty() )
        return;

    QString url = QString( "http://musicbrainz.org/recording/%1.html" ).arg( trackID );

    QDesktopServices::openUrl( url );
}
