gameStateChanged( KBounceGameWidget::State state )
{
    switch ( state )
    {
		case KBounceGameWidget::BeforeFirstGame :
			break;
		case KBounceGameWidget::BetweenLevels :
			break;
		case KBounceGameWidget::Suspended :
			break;
		case KBounceGameWidget::Paused :
		    m_pauseAction->setChecked( true );
		    m_statusBar->clearMessage();
		    break;
		case KBounceGameWidget::Running :
		    m_pauseAction->setChecked( false );
		    m_statusBar->clearMessage();
		    break;
		case KBounceGameWidget::GameOver :
		    statusBar()->showMessage(  i18n("Game over. Click to start a game") );
		    highscore();
		    break;
	    }
}
