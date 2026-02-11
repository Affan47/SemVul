clearAlbum()
{
    ui.albumLabel->clearText();
    ui.byCaption->hide();
    ui.albumLabel->hide();
    ui.releasedCaption->hide();
    ui.releaseDateLabel->clear();
    ui.recordLabelLabel->clear();
    ui.recordLabelLabel->hide();
    ui.totalCaption->hide();
    ui.numTracksLabel->clear();
    ui.buyAlbumIcon->hide();
    ui.buyAlbumIcon->setUrl( QUrl() );
    ui.buyAlbumLabel->clear();
    ui.buyAlbumLabel->setURL( QUrl() );
    QCursor cursor( Qt::ArrowCursor );
    ui.buyAlbumLabel->setUseCursor( true, &cursor );

    setDefaultAlbumCover();
    ui.albumPic->hide();
    ui.albumPic->setUrl ( QUrl() );

    adjustTrackLabels();
}
