processDefault(const std::string& argument, std::string& optionName, std::string& optionArg)
{
	std::string::const_iterator it  = argument.begin();
	std::string::const_iterator end = argument.end();
	if (it != end)
	{
		if (*it == '/')
		{
			++it;
			return processCommon(std::string(it, end), false, optionName, optionArg);
		}
	}
	return false;
}
