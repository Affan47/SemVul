handleOption(const std::string& name, const std::string& value)
{
	const Option& option = _options.getOption(name);
	if (option.validator())
	{
		option.validator()->validate(option, value);
	}
	if (!option.binding().empty())
	{
		AbstractConfiguration* pConfig = option.config();
		if (!pConfig) pConfig = &config();
		pConfig->setString(option.binding(), value);
	}
	if (option.callback())
	{
		option.callback()->invoke(name, value);
	}
}
