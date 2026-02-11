createTempFile(QString ext)
{

	string temp = gleInterface->getTempFile();
	return QString::fromUtf8(temp.c_str()) + ext;
}
