data()
{
	if (!isValid())
		return QByteArray();
	Stream *stream = m_embeddedFile->embFile() ? m_embeddedFile->embFile()->stream() : NULL;
	if (!stream)
		return QByteArray();

	stream->reset();
	int dataLen = 0;
	QByteArray fileArray;
	int i;
	while ( (i = stream->getChar()) != EOF) {
		fileArray[dataLen] = (char)i;
		++dataLen;
	}
	fileArray.resize(dataLen);
	return fileArray;
}
