moveTrackBookmark( Meta::TrackPtr track, qint64 newMiliseconds, QString name )
{
    qreal seconds = qreal ( newMiliseconds ) / 1000;
    QString trackPosition;
    trackPosition.setNum( seconds );

    QString trackName = track->prettyName();
    QString newName = ( trackName + " - " + Meta::msToPrettyTime( newMiliseconds ) );

    BookmarkModel::instance()->setBookmarkArg( name, "pos", trackPosition );
    BookmarkModel::instance()->renameBookmark( name, newName );
}
