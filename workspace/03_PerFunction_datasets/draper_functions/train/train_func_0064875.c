evaluatePoint(bool &ok,
					   const QString &parameterName,
					   const QString &subParameterName)
	{
		if(!ok)
			return QPoint();

		const SubParameter &subParameter = retreiveSubParameter(parameterName, subParameterName);
		QString result;

		if(subParameter.isCode())
		{
			QScriptValue evaluationResult = evaluateCode(ok, subParameter);
			if(Code::Point *codePoint = qobject_cast<Code::Point*>(evaluationResult.toQObject()))
				return codePoint->point();

			result = evaluationResult.toString();
		}
		else
			result = evaluateText(ok, subParameter);

		if(!ok)
			return QPoint();

		if(result.isEmpty() || result == ":")
			return QPoint();

		QStringList positionStringList = result.split(":");
		if(positionStringList.count() != 2)
		{
			ok = false;

            emit executionException(ActionException::InvalidParameterException, tr("\"%1\" is not a valid position.").arg(result));

			return QPoint();
		}

		QPoint point = QPoint(positionStringList.at(0).toInt(&ok), positionStringList.at(1).toInt(&ok));
		if(!ok)
		{
            emit executionException(ActionException::InvalidParameterException, tr("\"%1\" is not a valid position.").arg(result));

			return QPoint();
		}

		return point;
	}
