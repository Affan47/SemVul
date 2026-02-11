setupUi()
{
    ui.setupUi( this );

    ui.actionCheckForUpdates->setMenuRole( QAction::ApplicationSpecificRole );
    ui.actionAboutLastfm->setMenuRole( QAction::AboutRole );
    ui.actionSettings->setMenuRole( QAction::PreferencesRole );
    ui.actionStop->setVisible( false );
    ui.statusbar->addPermanentWidget( ui.scrobbleLabel = new ScrobbleLabel );


    QWidget *playControls = new QWidget;
    ui.playcontrols.setupUi( playControls );
    ui.toolbar->addWidget( playControls );


    ui.splitter->setCollapsible( 0, false );
    ui.splitter->setCollapsible( 1, false );
    ui.splitter->setStretchFactor( 0, 0 );
    ui.splitter->setStretchFactor( 1, 1 );


    QPalette p = centralWidget()->palette();
    p.setBrush( QPalette::Base, Qt::white );
    p.setBrush( QPalette::Text, Qt::black );
    centralWidget()->setPalette( p );


    ui.restStateWidget = new RestStateWidget( this );
    ui.metaDataWidget = new MetaDataWidget( this );


    ui.sidebar = new SideBarTree( this );
    ui.sidebarFrame->layout()->addWidget( ui.sidebar );
    ui.sidebarFrame->hide();
    connect( ui.sidebar, SIGNAL( statusMessage( QString ) ), SLOT( statusMessage( QString ) ) );
    connect( ui.sidebar, SIGNAL( plsShowRestState() ), SLOT( showRestState() ) );
    connect( ui.sidebar, SIGNAL( plsShowNowPlaying() ), SLOT( showMetaDataWidget() ) );


    ui.stack->setBackgroundRole( QPalette::Base );
    ui.stack->addWidget( ui.restStateWidget );
    ui.stack->addWidget( ui.metaDataWidget );

#ifdef HIDE_RADIO
    ui.playcontrols.volume->setVisible( false );
    ui.menuControls->menuAction()->setVisible( false );
    ui.actionPlay->setVisible( false );
    ui.actionStop->setVisible( false );
    ui.actionSkip->setVisible( false );
    ui.actionBan->setVisible( false );
    ui.actionPlaylist->setVisible( false );
    ui.actionToggleDiscoveryMode->setVisible( false );
    ui.actionVolumeUp->setVisible( false );
    ui.actionVolumeDown->setVisible( false );
    ui.actionMute->setVisible( false );

    ui.stack->removeWidget( ui.restStateWidget );
#endif

    if ( qApp->arguments().contains( "--debug" ) )
        ui.menuHelp->addAction( "kr4sh pls, kthxbai", this, SLOT( crash() ) );

    ui.restStateWidget->setFocus();
}
