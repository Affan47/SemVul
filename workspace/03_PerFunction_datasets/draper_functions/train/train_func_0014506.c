writeText(const QString &value, Encoding encoding)
	{
		if(mFile.write(toEncoding(value, encoding)) == -1)
			throwError("WriteFailedError", tr("Write failed"));

		return thisObject();
	}
