addEngine()
{
	EngineConfigurationDialog dlg(EngineConfigurationDialog::AddEngine, this);
	if (dlg.exec() == QDialog::Accepted)
		m_engineManager->addEngine(dlg.engineConfiguration());
}
