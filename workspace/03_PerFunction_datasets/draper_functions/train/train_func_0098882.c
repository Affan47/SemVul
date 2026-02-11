gunzip(const QString& path)
{
	QByteArray data;

	QFile file(path);
	if (!file.open(QFile::ReadOnly)) {
		return data;
	}
	gzFile gz = gzdopen(file.handle(), "rb");
	if (gz == NULL) {
		return data;
	}

	static const int buffer_size = 0x40000;
	char buffer[buffer_size];
	memset(buffer, 0, buffer_size);
	int read = 0;
	do {
		data.append(buffer, read);
		read = qMin(gzread(gz, buffer, buffer_size), buffer_size);
	} while (read > 0);
	gzclose(gz);

	return data;
}
