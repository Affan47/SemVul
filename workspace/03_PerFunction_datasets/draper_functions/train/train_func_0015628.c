mainLoadAux(const QString & fileName)
{
	if (fileName.isNull()) return;

    if (fileName.endsWith(".txt")) {
        QFileInfo info(fileName);
        QFile file(fileName);
        if (file.open(QFile::ReadOnly)) {
            QTextStream stream(&file);
            while (!stream.atEnd()) {
                QString line = stream.readLine().trimmed();
                foreach (QString ext, fritzingExtensions()) {
                    if (line.endsWith(ext)) {
                        QFileInfo lineInfo(line);
                        if (lineInfo.exists()) {
                            mainLoadAux(line);
                        }
                        else {
                            QFileInfo lineInfo(info.absoluteDir().absoluteFilePath(line));
                            if (lineInfo.exists()) {
                                mainLoadAux(lineInfo.absoluteFilePath());
                            }
                        }
                        break;
                    }
                }
            }
        }
        return;
    }

    if (!fileName.endsWith(FritzingSketchExtension) && !fileName.endsWith(FritzingBundleExtension)) {
        loadWhich(fileName, false, false, true, "");
        return;
    }

	if (alreadyOpen(fileName)) return;

	QFile file(fileName);
	if (!file.exists()) {
       FMessageBox::warning(this, tr("Fritzing"),
                             tr("Cannot find file %1.")
                             .arg(fileName));


		return;
	}


    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        FMessageBox::warning(this, tr("Fritzing"),
                             tr("Cannot read file  1 %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    file.close();

    MainWindow* mw = newMainWindow(m_referenceModel, fileName, true, true);
	mw->loadWhich(fileName, true, true, true, "");
    mw->clearFileProgressDialog();
	closeIfEmptySketch(mw);
}
