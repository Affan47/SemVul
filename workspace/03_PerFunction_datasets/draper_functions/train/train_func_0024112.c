save(const QString & fileName, bool asPart) {
	QFileInfo info(fileName);
	QDir dir = info.absoluteDir();

	QString temp = dir.absoluteFilePath("temp.xml");
    QFile file1(temp);
    if (!file1.open(QFile::WriteOnly | QFile::Text)) {
        FMessageBox::warning(NULL, QObject::tr("Fritzing"),
                             QObject::tr("Cannot write file temp:\n%1\n%2\n%3.")
							  .arg(temp)
							  .arg(fileName)
                              .arg(file1.errorString())
							  );
        return;
    }

    QXmlStreamWriter streamWriter(&file1);
	save(fileName, streamWriter, asPart);
	file1.close();
	QFile original(fileName);
	if(original.exists() && !original.remove()) {
		file1.remove();
		FMessageBox::warning(
			NULL,
			tr("File save failed!"),
			tr("Couldn't overwrite file '%1'.\nReason: %2 (errcode %3)")
				.arg(fileName)
				.arg(original.errorString())
				.arg(original.error())
			);
		return;
	}
	file1.rename(fileName);
}
