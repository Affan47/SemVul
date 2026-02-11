evaluatePolygon(bool &ok,
					   const QString &parameterName,
					   const QString &subParameterName)
	{
		if(!ok)
			return QPolygon();

		const SubParameter &subParameter = retreiveSubParameter(parameterName, subParameterName);
		QString result;

		if(subParameter.isCode())
			result = evaluateCode(ok, subParameter).toString();
		else
			result = evaluateText(ok, subParameter);

		if(!ok)
			return QPolygon();

		if(result.isEmpty() || result == ";")
			return QPolygon();

		QStringList pointStrings = result.split(';', QString::SkipEmptyParts);
		QPolygon polygon;

		foreach(const QString &pointString, pointStrings)
		{
			QStringList pointComponents = pointString.split(':', QString::SkipEmptyParts);
			if(pointComponents.size() != 2)
				continue;

			polygon << QPoint(pointComponents.at(0).toInt(), pointComponents.at(1).toInt());
		}

		return polygon;
	}
