configureLogger(AbstractConfiguration* pConfig)
{
	Logger& logger = Logger::get(pConfig->getString("name", ""));
	AbstractConfiguration::Keys props;
	pConfig->keys(props);
	for (AbstractConfiguration::Keys::const_iterator it = props.begin(); it != props.end(); ++it)
	{
		if (*it == "channel" && pConfig->hasProperty("channel.class"))
		{
			AutoPtr<AbstractConfiguration> pChannelConfig(pConfig->createView(*it));
			AutoPtr<Channel> pChannel(createChannel(pChannelConfig));
			configureChannel(pChannel, pChannelConfig);
			Logger::setChannel(logger.name(), pChannel);
		}
		else if (*it != "name")
		{
			Logger::setProperty(logger.name(), *it, pConfig->getString(*it));
		}
	}
}
