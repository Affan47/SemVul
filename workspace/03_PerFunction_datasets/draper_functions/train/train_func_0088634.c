newSession()
{

	QString name = getSessionName(tr("New Session"));
	if (name.isEmpty()) {
		return;
	}
	QString theme = m_session->theme();


	bool visible = isVisible();
	hide();
	if (!closeCurrent()) {
		if (visible) {
			show();
		}
		return;
	}
	accept();


	{
		QSettings session(Session::pathFromName(name), QSettings::IniFormat);
		session.setValue("ThemeManager/Theme", theme);
		session.setValue("ThemeManager/Size", QSettings().value("ThemeManager/Size"));
	}
	setCurrent(name);
}
