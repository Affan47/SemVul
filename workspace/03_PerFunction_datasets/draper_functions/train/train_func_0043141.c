writeUtf8(const QString & fileName, const QString & text)
{
	QFile file(fileName);
	if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
		QTextStream out(&file);
		out.setCodec("UTF-8");
		out << text;
		file.close();
        return true;
    }

    return false;
}
