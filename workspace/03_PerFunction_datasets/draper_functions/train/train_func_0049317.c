loadLastOpenSketch() {
	QList<MainWindow *> sketches;
	QSettings settings;
	if(settings.value("lastOpenSketch").isNull()) return sketches;

	QString lastSketchPath = settings.value("lastOpenSketch").toString();
	if(!QFileInfo(lastSketchPath).exists()) {
		settings.remove("lastOpenSketch");
		return sketches;
	}

    DebugDialog::debug(QString("Loading last open sketch %1").arg(lastSketchPath));
    settings.remove("lastOpenSketch");
    MainWindow *mainWindow = MainWindow::newMainWindow(m_referenceModel, lastSketchPath, true, true);
    mainWindow->loadWhich(lastSketchPath, true, true, true, "");
    sketches << mainWindow;
    settings.setValue("lastOpenSketch", lastSketchPath);
	return sketches;
}
