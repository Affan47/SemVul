evaluateVariable(bool &ok,
										const QString &parameterName,
										const QString &subParameterName)
	{
		QString result = evaluateString(ok, parameterName, subParameterName);

		if(!ok)
			return 0;

        if(!result.isEmpty() && !NameRegExp.exactMatch(result))
		{
			ok = false;

            emit executionException(ActionException::InvalidParameterException, tr("A variable name can only contain alphanumeric characters and cannot start with a digit."));

			return QString();
		}

		return result;
	}
