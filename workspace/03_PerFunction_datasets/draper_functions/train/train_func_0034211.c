parseUciTokens(const QStringRef& first,
				     const QString* types,
				     int typeCount,
				     QVarLengthArray<QStringRef>& tokens,
				     int& type)
{
	QStringRef token(first);
	type = -1;
	tokens.clear();

	do
	{
		bool newType = false;
		for (int i = 0; i < typeCount; i++)
		{
			if (token == types[i])
			{
				if (type != -1)
					return token;
				type = i;
				newType = true;
				break;
			}
		}
		if (!newType && type != -1)
			tokens.append(token);
	}
	while (!(token = nextToken(token)).isNull());

	return token;
}
