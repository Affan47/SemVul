constructFileName(const QString & differentiator, const QString & suffix) {
	QString fn = QFileInfo(m_fwFilename).completeBaseName();
	fn += "_" + (differentiator.isEmpty() ? m_currentGraphicsView->getShortName() : differentiator);
	return fn + suffix;
}
