createMimeDataFromSelection() const
	{
		QMimeData* mime = QTextEdit::createMimeDataFromSelection();
		QByteArray rtf = mimeToRtf(mime);
		mime->setData(QLatin1String("text/rtf"), rtf);
		mime->setData(QLatin1String("text/richtext"), rtf);
		mime->setData(QLatin1String("application/rtf"), rtf);
		return mime;
	}
