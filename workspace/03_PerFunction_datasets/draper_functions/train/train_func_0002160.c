demo()
{
	if(
		m_scores &&
		!m_scores -> allScores() &&
		!m_scores -> currentPlayer().noScores() &&
		KMessageBox::warningContinueCancel(
			this,
			i18n("Starting the demo will end the current game. Any progress will be lost. Do you want to continue?")
		) == KMessageBox::Cancel
	)
	{
		m_demoAction -> setChecked(false);
		return;
	}

	bool preDemoHumans[6];
	preDemoHumans[0] = kirikiSettings::player1IsHuman();
	preDemoHumans[1] = kirikiSettings::player2IsHuman();
	preDemoHumans[2] = kirikiSettings::player3IsHuman();
	preDemoHumans[3] = kirikiSettings::player4IsHuman();
	preDemoHumans[4] = kirikiSettings::player5IsHuman();
	preDemoHumans[5] = kirikiSettings::player6IsHuman();
	int preDemoNumPlayers = kirikiSettings::numberOfPlayers();
	kirikiSettings::setPlayer1IsHuman(false);
	kirikiSettings::setPlayer2IsHuman(false);
	kirikiSettings::setPlayer3IsHuman(false);
	kirikiSettings::setPlayer4IsHuman(false);
	kirikiSettings::setPlayer5IsHuman(false);
	kirikiSettings::setPlayer6IsHuman(false);
	kirikiSettings::setNumberOfPlayers(6);
	newGame();
	emit demoStarted();
	disconnect(m_lateral, SIGNAL(rolled()), statusBar(), SLOT(hide()));
	kirikiSettings::setPlayer1IsHuman(preDemoHumans[0]);
	kirikiSettings::setPlayer2IsHuman(preDemoHumans[1]);
	kirikiSettings::setPlayer3IsHuman(preDemoHumans[2]);
	kirikiSettings::setPlayer4IsHuman(preDemoHumans[3]);
	kirikiSettings::setPlayer5IsHuman(preDemoHumans[4]);
	kirikiSettings::setPlayer6IsHuman(preDemoHumans[5]);
	kirikiSettings::setNumberOfPlayers(preDemoNumPlayers);
	statusBar()->showMessage(i18n("Demonstration. Press \"New\" to start a new game."));
	statusBar()->show();
	m_lateral->enableDemoMode();
}
