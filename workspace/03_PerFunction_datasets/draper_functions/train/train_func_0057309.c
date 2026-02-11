configure(AbstractConfiguration* pConfig)
{
	poco_check_ptr (pConfig);

	AutoPtr<AbstractConfiguration> pFormattersConfig(pConfig->createView("logging.formatters"));
	configureFormatters(pFormattersConfig);

	AutoPtr<AbstractConfiguration> pChannelsConfig(pConfig->createView("logging.channels"));
	configureChannels(pChannelsConfig);

	AutoPtr<AbstractConfiguration> pLoggersConfig(pConfig->createView("logging.loggers"));
	configureLoggers(pLoggersConfig);
}
