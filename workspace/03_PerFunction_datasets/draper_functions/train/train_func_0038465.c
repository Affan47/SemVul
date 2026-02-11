runKicadSchematicService() {
	QDir dir(m_outputFolder);
	QStringList filters;
	filters << "*.lib";
	QStringList filenames = dir.entryList(filters, QDir::Files);
	foreach (QString filename, filenames) {
		QString filepath = dir.absoluteFilePath(filename);
		QStringList defNames = KicadSchematic2Svg::listDefs(filepath);
		foreach (QString defName, defNames) {
			KicadSchematic2Svg kicad;
			try {
				QString svg = kicad.convert(filepath, defName);
				if (svg.isEmpty()) {
					DebugDialog::debug("svg is empty " + filepath + " " + defName);
					continue;
				}
				foreach (QChar c, QString("<>:\"/\\|?*")) {
					defName.remove(c);
				}


				QString newFilePath = dir.absoluteFilePath(defName + "_" + filename);
				newFilePath.replace(".lib", ".svg");

				QFile file(newFilePath);
				if (!TextUtils::writeUtf8(newFilePath, svg)) {
					DebugDialog::debug("unable to open file " + newFilePath);
				}
			}
			catch (const QString & msg) {
				DebugDialog::debug(msg);
			}
			catch (...) {
				DebugDialog::debug("who knows");
			}
		}
	}
}
