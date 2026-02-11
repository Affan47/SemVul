isMatch(QString text1, QString text2)
{
	int text2Length = text2.count();
	int curChar = 0;

	foreach(QChar c, text1)
	{
		if (c.toLower() == text2[curChar].toLower())
		{
			++curChar;
			if (curChar >= text2Length)
			{
				return true;
			}
		}
	}

	return false;
}
