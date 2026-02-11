downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
	{
		if(bytesTotal == -1)
			return;

		if(mOnDownloadProgress.isValid())
			mOnDownloadProgress.call(thisObject(), QScriptValueList() << static_cast<qsreal>(bytesReceived) << static_cast<qsreal>(bytesTotal));
	}
