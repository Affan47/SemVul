runGerberServiceAux()
{
	QDir dir(m_outputFolder);
	QString s = dir.absolutePath();
	QStringList filters;
	filters << "*" + FritzingBundleExtension;
	QStringList filenames = dir.entryList(filters, QDir::Files);
	foreach (QString filename, filenames) {
		QString filepath = dir.absoluteFilePath(filename);
		MainWindow * mainWindow = openWindowForService(false);
		m_started = true;

		FolderUtils::setOpenSaveFolderAux(m_outputFolder);
		if (mainWindow->loadWhich(filepath, false, false, false, "")) {
            QFileInfo info(filepath);
            GerberGenerator::exportToGerber(info.completeBaseName(), m_outputFolder, NULL, mainWindow->pcbView(), false);
		}

		mainWindow->setCloseSilently(true);
		mainWindow->close();
	}
}
