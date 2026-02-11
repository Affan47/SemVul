drivers(QScriptContext *context, QScriptEngine *engine)
	{
		Q_UNUSED(context)

		QStringList driverNames = QSqlDatabase::drivers();
		QSet<Driver> driverList;

		for(int index = 0; index < driverNames.size(); ++index)
		{
			const QString &driverNameToInclude = driverNames.at(index);

			for(int driverIndex = 0; driverIndex < DriverCount; ++driverIndex)
			{
				if(driverName(static_cast<Driver>(driverIndex)) == driverNameToInclude)
					driverList.insert(static_cast<Driver>(driverIndex));
			}
		}

		QScriptValue back = engine->newArray(driverList.size());
		int index = 0;
		foreach(const Driver &driver, driverList)
		{
			back.setProperty(index, driver);

			++index;
		}

		return back;
	}
