checkForUpdates(bool atUserRequest)
{
	if (atUserRequest) {
		enableCheckUpdates(false);
	}

	VersionChecker * versionChecker = new VersionChecker();

	QSettings settings;
	if (!atUserRequest) {

		QString lastMainVersionChecked = settings.value("lastMainVersionChecked").toString();
		if (!lastMainVersionChecked.isEmpty()) {
			versionChecker->ignore(lastMainVersionChecked, false);
		}
		QString lastInterimVersionChecked = settings.value("lastInterimVersionChecked").toString();
		if (!lastInterimVersionChecked.isEmpty()) {
			versionChecker->ignore(lastInterimVersionChecked, true);
		}
	}

    QString atom = QString("http://fritzing.org/download/feed/atom/%1/%2")
		.arg(PLATFORM_NAME)
		.arg(Version::makeRequestParamsString(true));
    DebugDialog::debug(atom);
    versionChecker->setUrl(atom);
	m_updateDialog->setAtUserRequest(atUserRequest);
	m_updateDialog->setVersionChecker(versionChecker);

	if (atUserRequest) {
		m_updateDialog->show();
	}
}
