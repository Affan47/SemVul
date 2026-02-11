processUnix(const std::string& argument, std::string& optionName, std::string& optionArg)
{
	std::string::const_iterator it  = argument.begin();
	std::string::const_iterator end = argument.end();
	if (it != end)
	{
		if (*it == '-')
		{
			++it;
			if (it != end)
			{
				if (*it == '-')
				{
					++it;
					if (it == end)
					{
						_ignore = true;
						return true;
					}
					else return processCommon(std::string(it, end), false, optionName, optionArg);
				}
				else return processCommon(std::string(it, end), true, optionName, optionArg);
			}
		}
	}
	return false;
}
