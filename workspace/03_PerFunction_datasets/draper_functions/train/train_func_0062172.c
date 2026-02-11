loadFromFile(const QString &filename)
	{
		if(!mImage.load(filename))
		{
			throwError("LoadImageError", tr("Unable to load image from file %1").arg(filename));
			return thisObject();
		}

		return thisObject();
	}
