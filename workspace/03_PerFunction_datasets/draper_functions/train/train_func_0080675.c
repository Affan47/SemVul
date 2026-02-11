process(const std::string& argument, std::string& optionName, std::string& optionArg)
{
	optionName.clear();
	optionArg.clear();
	if (!_ignore)
	{
		if (!_deferredOption.empty())
			return processCommon(argument, false, optionName, optionArg);
		else if (_unixStyle)
			return processUnix(argument, optionName, optionArg);
		else
			return processDefault(argument, optionName, optionArg);
	}
	return false;
}
