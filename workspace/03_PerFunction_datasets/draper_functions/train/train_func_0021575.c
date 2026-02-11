setConfigElement( KNotifyConfigElement * config )
{
	bool blocked = blockSignals(true);
	QString prstring=config->readEntry( "Action" );
	QStringList actions=prstring.split ('|');

	m_ui.Sound_check->setChecked( actions.contains("Sound") );
	m_ui.Popup_check->setChecked( actions.contains("Popup") );
	m_ui.Logfile_check->setChecked( actions.contains("Logfile") );
	m_ui.Execute_check->setChecked( actions.contains("Execute") );
	m_ui.Taskbar_check->setChecked( actions.contains("Taskbar") );
	m_ui.KTTS_check->setChecked( actions.contains("KTTS") );

	m_ui.Sound_select->setUrl( KUrl( config->readEntry( "Sound" , true ) ) );
	m_ui.Logfile_select->setUrl( KUrl( config->readEntry( "Logfile" , true ) ) );
	m_ui.Execute_select->setUrl( KUrl( config->readEntry( "Execute"  ) ) );
	m_ui.KTTS_select->setText( config->readEntry( "KTTS"  )  );
	if(m_ui.KTTS_select->text() == QLatin1String("%e"))
		m_ui.KTTS_combo->setCurrentIndex(1);
	else if(m_ui.KTTS_select->text() == QLatin1String("%m") || m_ui.KTTS_select->text() == QLatin1String("%s"))
		m_ui.KTTS_combo->setCurrentIndex(0);
	else
		m_ui.KTTS_combo->setCurrentIndex(2);
	blockSignals(blocked);
}
