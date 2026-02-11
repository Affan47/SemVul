openGame() {
	cleanUp();
	emit loading();

	QSettings settings;
	m_pattern = Pattern::create(settings.value("Current/Pattern").toInt());
	m_pattern->setCount(settings.value("Current/Count").toInt());
	m_pattern->setLength(settings.value("Current/Length").toInt());
	m_pattern->setSeed(settings.value("Current/Seed").toInt());

	connect(m_pattern, SIGNAL(generated()), this, SLOT(patternGenerated()));
	m_pattern->start();
}
