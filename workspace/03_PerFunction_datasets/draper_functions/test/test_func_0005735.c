initActions()
{
	_actions.resize( NB_ACTIONS );

	QAction * action;
	QSignalMapper * sigmap = new QSignalMapper( this );

	addAction( tr( "&Connect to server" ), QKeySequence( tr( "CTRL+C" ) ), ACTION_CONNECT, sigmap );
	action = addAction( tr( "&Disconnect" ), QKeySequence( tr( "CTRL+D" ) ), ACTION_DISCONNECT, sigmap );
	action->setEnabled( false );

	QActionGroup * groupLog = new QActionGroup( this );
	action = addAction( tr( "Verbose" ), QKeySequence( tr( "" ) ), ACTION_LOGVERBOSE, sigmap );
	action->setCheckable( true );
	groupLog->addAction( action );
	action = addAction( tr( "Normal" ), QKeySequence( tr( "" ) ), ACTION_LOGNORMAL, sigmap );
	action->setCheckable( true );
	groupLog->addAction( action );
	action->setChecked( true );
	action = addAction( tr( "Critical" ), QKeySequence( tr( "" ) ), ACTION_LOGCRITICAL, sigmap );
	action->setCheckable( true );
	groupLog->addAction( action );
	action = addAction( tr( "Quiet" ), QKeySequence( tr( "" ) ), ACTION_LOGQUIET, sigmap );
	action->setCheckable( true );
	groupLog->addAction( action );
	action = addAction( tr( "&Quit" ), QKeySequence( tr( "CTRL+Q" ) ), ACTION_QUIT, sigmap );

	connect( sigmap, SIGNAL( mapped( int ) ), SLOT( slot_action( int ) ) );
}
