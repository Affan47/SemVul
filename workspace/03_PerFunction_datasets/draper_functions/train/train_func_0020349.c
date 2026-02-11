showEvent( QShowEvent *ev )
{
    EngineController *engine = The::engineController();

    connect( engine, SIGNAL(stopped(qint64,qint64)),
             this, SLOT(stopped()) );
    connect( engine, SIGNAL(paused()),
             this, SLOT(paused()) );
    connect( engine, SIGNAL(trackPlaying(Meta::TrackPtr)),
             this, SLOT(playing()) );

    connect( engine, SIGNAL(trackChanged(Meta::TrackPtr)),
             this, SLOT(trackChanged(Meta::TrackPtr)) );
    connect( engine, SIGNAL(trackMetadataChanged(Meta::TrackPtr)),
             this, SLOT(trackChanged(Meta::TrackPtr)) );
    connect( engine, SIGNAL(trackLengthChanged(qint64)),
             this, SLOT(trackLengthChanged(qint64)) );
    connect( engine, SIGNAL(trackPositionChanged(qint64,bool)),
             this, SLOT(trackPositionChanged(qint64,bool)) );
    connect( engine, SIGNAL(volumeChanged(int)),
             this, SLOT(volumeChanged(int)) );
    connect( engine, SIGNAL(muteStateChanged(bool)),
             this, SLOT(muteStateChanged(bool)) );


    connect( The::playlistController(), SIGNAL(changed()),
              this, SLOT(updatePrevAndNext()) );

    connect( The::playlist()->qaim(), SIGNAL(queueChanged()),
              this, SLOT(updatePrevAndNext()) );

    connect( The::playlistActions(), SIGNAL(navigatorChanged()),
                 this, SLOT(updatePrevAndNext()) );

    connect( The::amarokUrlHandler(), SIGNAL(timecodesUpdated(const QString*)),
              this, SLOT(updateBookmarks(const QString*)) );
    connect( The::amarokUrlHandler(), SIGNAL(timecodeAdded(QString,int)),
              this, SLOT(addBookmark(QString,int)) );

    QToolBar::showEvent( ev );
    trackChanged( The::engineController()->currentTrack() );
    layoutTrackBar();
    layoutProgressBar();
    m_playPause->setPlaying( The::engineController()->isPlaying() );
}
