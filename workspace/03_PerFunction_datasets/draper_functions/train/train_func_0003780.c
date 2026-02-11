configureChannel(Channel* pChannel, AbstractConfiguration* pConfig)
{
	AbstractConfiguration::Keys props;
	pConfig->keys(props);
	for (AbstractConfiguration::Keys::const_iterator it = props.begin(); it != props.end(); ++it)
	{
		if (*it != "pattern" && *it != "formatter" && *it != "class")
		{
			pChannel->setProperty(*it, pConfig->getString(*it));
		}
	}
}
