showSettings(){
	if (KConfigDialog::showDialog(QLatin1String( "settings" )))
		return;

	m_generalConfigDialog = new General();

	if (Settings::gameType() == Settings::EnumGameType::Snake) {
		m_generalConfigDialog->namePlayer1Label->setText(i18n("Player Name:"));
		m_generalConfigDialog->namePlayer2Label->setText(i18n("Opponent:"));
	}
	else {
		m_generalConfigDialog->namePlayer1Label->setText(i18n("Right Player:"));
		m_generalConfigDialog->namePlayer2Label->setText(i18n("Left Player:"));
	}

	KConfigDialog *dialog = new KConfigDialog(this, QLatin1String( "settings" ), Settings::self());
	dialog->addPage(m_generalConfigDialog, i18n("General"), QLatin1String( "games-config-options" ));
	dialog->addPage(new KGameThemeSelector(dialog, Settings::self(), KGameThemeSelector::NewStuffEnableDownload), i18n("Theme"), QLatin1String( "games-config-theme" ));
	connect(dialog, SIGNAL(settingsChanged(QString)), this, SLOT(loadSettings()));
	connect(dialog, SIGNAL(settingsChanged(QString)), m_tron, SLOT(loadSettings()));
	dialog->show();
}
