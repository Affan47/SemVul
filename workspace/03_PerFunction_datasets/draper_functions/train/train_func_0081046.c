updatePrefs(PrefsDialog & prefsDialog)
{
	QSettings settings;

	if (prefsDialog.cleared()) {
		settings.clear();
		return;
	}

	QHash<QString, QString> hash = prefsDialog.settings();
	QList<MainWindow *> mainWindows = orderedTopLevelMainWindows();
	foreach (QString key, hash.keys()) {
		settings.setValue(key, hash.value(key));
		if (key.compare("connectedColor") == 0) {
			QColor c(hash.value(key));
			ItemBase::setConnectedColor(c);
			foreach (MainWindow * mainWindow, mainWindows) {
				mainWindow->redrawSketch();
			}
		}
		else if (key.compare("unconnectedColor") == 0) {
			QColor c(hash.value(key));
			ItemBase::setUnconnectedColor(c);
			foreach (MainWindow * mainWindow, mainWindows) {
				mainWindow->redrawSketch();
			}
		}
		else if (key.compare("wheelMapping") == 0) {
			ZoomableGraphicsView::setWheelMapping((ZoomableGraphicsView::WheelMapping) hash.value(key).toInt());
		}
		else if (key.compare("autosavePeriod") == 0) {
			MainWindow::setAutosavePeriod(hash.value(key).toInt());
		}
		else if (key.compare("autosaveEnabled") == 0) {
			MainWindow::setAutosaveEnabled(hash.value(key).toInt());
		}
		else if (key.contains("curvy", Qt::CaseInsensitive)) {
			foreach (MainWindow * mainWindow, mainWindows) {
				foreach (SketchWidget * sketchWidget, mainWindow->sketchWidgets()) {
					if (key.contains(sketchWidget->getShortName())) {
						sketchWidget->setCurvyWires(hash.value(key).compare("1") == 0);
					}
				}
			}
		}
	}

}
