loadTranslator(const QString& name, const QStringList& datadirs)
{
	m_appname = name;


	QStringList paths = datadirs;
	if (paths.isEmpty()) {
		QString appdir = QCoreApplication::applicationDirPath();
		paths.append(appdir);
		paths.append(appdir + "/../share/" + QCoreApplication::applicationName().toLower());
		paths.append(appdir + "/../Resources");
	}
	foreach (const QString& path, paths) {
		if (QFile::exists(path + "/translations/")) {
			m_path = path + "/translations/";
			break;
		}
	}


	m_current = QSettings().value("Locale/Language").toString();
	QString current = !m_current.isEmpty() ? m_current : QLocale::system().name();
	QStringList translations = findTranslations();
	if (!translations.contains(m_appname + current)) {
		current = current.left(2);
		if (!translations.contains(m_appname + current)) {
			current.clear();
		}
	}
	if (!current.isEmpty()) {
		QLocale::setDefault(current);
	} else {
		current = "en";
	}


	static QTranslator qt_translator;
	if (translations.contains("qt_" + current) || translations.contains("qt_" + current.left(2))) {
		qt_translator.load("qt_" + current, m_path);
	} else {
		qt_translator.load("qt_" + current, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	}
	QCoreApplication::installTranslator(&qt_translator);

	static QTranslator translator;
	translator.load(m_appname + current, m_path);
	QCoreApplication::installTranslator(&translator);
}
