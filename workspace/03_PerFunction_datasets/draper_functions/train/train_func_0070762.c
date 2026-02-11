evaluateVariableArray(bool &ok, const QScriptValue &scriptValue)
	{
		QString result;

		QScriptValueIterator it(scriptValue);

		if(scriptValue.isArray())
		{
			int lastIndex = -1;
			result = "[";

			while (it.hasNext()) {
				it.next();

				if (it.flags() & QScriptValue::SkipInEnumeration)
					continue;

				QScriptValue nextScriptValue = it.value();

				if(nextScriptValue.isArray())
					result += evaluateVariableArray(ok, nextScriptValue);
				else
                    if(NumericalIndex.exactMatch(it.name()))
					{
						int newIndex = it.name().toInt();
						if( newIndex > lastIndex+1)
						{

							for(lastIndex++ ; lastIndex < newIndex; lastIndex++ )
								result += ",";
						}
						lastIndex = newIndex;
						result += it.value().toString();
					}
					else
						result += it.name().append("=").append(it.value().toString());

				result += ",";
			}

			if(result == "[")
				result += "]";
			else
				result[result.lastIndexOf(",")] = QChar(']');
		}
		else
			result = it.value().toString();

		return result;
	}
