configureWhiteEngine()
{
	EngineConfigurationDialog dlg(EngineConfigurationDialog::ConfigureEngine, this);

	int i = selectedEngineIndex(Chess::Side::White);
	dlg.applyEngineInformation(
		CuteChessApplication::instance()->engineManager()->engines().at(i));

	if (dlg.exec() == QDialog::Accepted)
	{
		CuteChessApplication::instance()->engineManager()->updateEngineAt(i,
			dlg.engineConfiguration());
	}
}
