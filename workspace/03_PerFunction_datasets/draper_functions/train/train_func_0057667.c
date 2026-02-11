getOpenFileName(QWidget* parent, const QString& caption, const QString& filter, QString* selectedFilter)
{
	while (1) {
		if (lastUsedOpenPath().isEmpty()) {
			setLastUsedOpenPath(QDir::homeDirPath());
		}
		QString fileName = QFileDialog::getOpenFileName(parent, caption, lastUsedOpenPath(), filter, selectedFilter);
		if (!fileName.isEmpty()) {
			QFileInfo fi(fileName);
			if (!fi.exists()) {
				QMessageBox::information(parent, tr("Error"), tr("The file specified does not exist."));
				continue;
			}

			setLastUsedOpenPath(fi.dirPath());
			return fileName;
		}
		break;
	}

	return QString();
}
