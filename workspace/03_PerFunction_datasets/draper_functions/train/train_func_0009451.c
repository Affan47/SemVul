updateCurrentTrackActions()
{

    QLayoutItem *item;
    while ( (item = m_current.label->layout()->takeAt(0)) )
    {
        delete item->widget();
        delete item;
    }


    QList<QAction*> actions;

    foreach( QAction* action, The::globalCurrentTrackActions()->actions() )
        actions << action;

    Meta::TrackPtr track = The::engineController()->currentTrack();
    if( track )
    {
        QScopedPointer< Capabilities::ActionsCapability > ac( track->create<Capabilities::ActionsCapability>() );
        if( ac )
            actions << ac->actions();

        QScopedPointer< Capabilities::BookmarkThisCapability > btc( track->create<Capabilities::BookmarkThisCapability>() );
        if( btc && btc->bookmarkAction() )
            actions << btc->bookmarkAction();
    }

    QHBoxLayout *hbl = static_cast<QHBoxLayout*>( m_current.label->layout() );
    hbl->setContentsMargins( 0, 0, 0, 0 );
    hbl->setSpacing( track_action_spacing );

    TrackActionButton *btn;
    const int n = actions.count() / 2;
    for ( int i = 0; i < actions.count(); ++i )
    {
        if( i == n )
            hbl->addStretch( 10 );
        btn = new TrackActionButton( m_current.label, actions.at(i) );
        if( !actions.at(i)->parent() )
            actions.at(i)->setParent(btn);
        btn->installEventFilter( this );
        hbl->addWidget( btn );
    }
}
