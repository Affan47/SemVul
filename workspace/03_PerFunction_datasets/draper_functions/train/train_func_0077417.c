deleteKey(const QString &keyName)
	{
		if(!mConfig.deleteData(toEncoding(keyName, mEncoding)))
		{
			throwError("FindSectionError", tr("Cannot delete key named \"%1\"").arg(keyName));
			return thisObject();
		}

		return thisObject();
	}
