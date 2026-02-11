saveAs(const QString & filename, bool readOnly) {
	DebugDialog::debug(QString("current path: %1").arg(QDir::currentPath()));
	QString fileExt;
    QString path;
    QString untitledBase = untitledFileName();

	if(readOnly) {
		path = defaultSaveFolder() + "/" + QFileInfo(filename).fileName();
    }
	else if(filename.startsWith(untitledBase, Qt::CaseInsensitive)) {
		path = defaultSaveFolder() + "/" + filename;
	}
	else if(filename.isNull() || filename.isEmpty()) {
		path = defaultSaveFolder();
	}
	else {
		path = filename;
	}
	DebugDialog::debug(QString("current file: %1").arg(filename));
    QString newFilename = FolderUtils::getSaveFileName(
						this,
                        tr("Specify a file name"),
                        path,
                        getExtensionString(),
                        &fileExt
                      );

    if (newFilename.isEmpty()) return false;

	if (readOnly && (newFilename.compare(filename, Qt::CaseInsensitive) == 0)) {
        QMessageBox::warning(NULL, QObject::tr("Fritzing"),
                     QObject::tr("The file '%1' is read-only; please use a different filename.")
                     .arg(newFilename) );
		return false;

	}

    FileProgressDialog progress("Saving...", 0, this);

	QStringList extensions = getExtensions();
    bool hasExtension = false;
	foreach (QString extension, extensions) {
		if(alreadyHasExtension(newFilename, extension)) {
			hasExtension = true;
			break;
		}
	}

	if (!hasExtension) {
		newFilename += extensions[0];
	}

	return saveAsAux(newFilename);
}
