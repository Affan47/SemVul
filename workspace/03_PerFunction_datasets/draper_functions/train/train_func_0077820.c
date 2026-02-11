getOpenDataFileName(QWidget *parent,
					const QString &caption,
					const QString &filter,
					QString *selectedFilter)
{
    if (lastDataDir == "")
        lastDataDir = QDir::currentPath();

    QString filePath = QFileDialog::getOpenFileName(parent, caption,
						    lastDataDir, filter,
						    selectedFilter);
    if (filePath != "") {
	QFileInfo info(filePath);
	lastDataDir  = info.absolutePath();
	lastBaseName = info.completeBaseName();


    }
    return filePath;
}
