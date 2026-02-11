configureChannels(AbstractConfiguration* pConfig)
{
	AbstractConfiguration::Keys channels;
	pConfig->keys(channels);
	for (AbstractConfiguration::Keys::const_iterator it = channels.begin(); it != channels.end(); ++it)
	{
		AutoPtr<AbstractConfiguration> pChannelConfig(pConfig->createView(*it));
		AutoPtr<Channel> pChannel = createChannel(pChannelConfig);
		LoggingRegistry::defaultRegistry().registerChannel(*it, pChannel);
	}
	for (AbstractConfiguration::Keys::const_iterator it = channels.begin(); it != channels.end(); ++it)
	{
		AutoPtr<AbstractConfiguration> pChannelConfig(pConfig->createView(*it));
		Channel* pChannel = LoggingRegistry::defaultRegistry().channelForName(*it);
		configureChannel(pChannel, pChannelConfig);
	}
}
