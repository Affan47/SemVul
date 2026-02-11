createChannel(AbstractConfiguration* pConfig)
{
	AutoPtr<Channel> pChannel(LoggingFactory::defaultFactory().createChannel(pConfig->getString("class")));
	AutoPtr<Channel> pWrapper(pChannel);
	AbstractConfiguration::Keys props;
	pConfig->keys(props);
	for (AbstractConfiguration::Keys::const_iterator it = props.begin(); it != props.end(); ++it)
	{
		if (*it == "pattern")
		{
			AutoPtr<Formatter> pPatternFormatter(new PatternFormatter(pConfig->getString(*it)));
			pWrapper = new FormattingChannel(pPatternFormatter, pChannel);
		}
		else if (*it == "formatter")
		{
			AutoPtr<FormattingChannel> pFormattingChannel(new FormattingChannel(0, pChannel));
			if (pConfig->hasProperty("formatter.class"))
			{
				AutoPtr<AbstractConfiguration> pFormatterConfig(pConfig->createView(*it));
				AutoPtr<Formatter> pFormatter(createFormatter(pFormatterConfig));
				pFormattingChannel->setFormatter(pFormatter);
			}
			else pFormattingChannel->setProperty(*it, pConfig->getString(*it));
#if defined(__GNUC__) && __GNUC__ < 3
			pWrapper = pFormattingChannel.duplicate();
#else
			pWrapper = pFormattingChannel;
#endif
		}
	}
	return pWrapper.duplicate();
}
