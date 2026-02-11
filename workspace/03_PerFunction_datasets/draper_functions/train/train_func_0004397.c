isPathExclued(const string &subPath)
{
	bool retVal = false;


	for (size_t i = 0; i < excludeVector.size(); i++)
	{
		string exclude = excludeVector[i];

		if (subPath.length() < exclude.length())
			continue;

		size_t compareStart = subPath.length() - exclude.length();

		if (compareStart > 0)
		{
			char lastPathChar = subPath[compareStart - 1];
			if (lastPathChar != g_fileSeparator)
				continue;
		}

		string compare = subPath.substr(compareStart);
		if (!g_isCaseSensitive)
		{

			for (size_t j = 0; j < compare.length(); j++)
				compare[j] = (char)tolower(compare[j]);
			for (size_t j = 0; j < exclude.length(); j++)
				exclude[j] = (char)tolower(exclude[j]);
		}

		if (compare == exclude)
		{
			excludeHitsVector[i] = true;
			retVal = true;
			break;
		}
	}
	return retVal;
}
