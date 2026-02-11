saveSettings()
{
	QSettings settings("gnuplot", "qtterminal");
	settings.setValue("view/antialias", m_antialias);
	settings.setValue("view/rounded", m_rounded);
	settings.setValue("view/backgroundColor", m_backgroundColor);
	settings.setValue("view/replotOnResize", m_replotOnResize);
}
