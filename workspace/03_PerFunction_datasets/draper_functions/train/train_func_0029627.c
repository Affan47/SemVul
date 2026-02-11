add(AbstractConfiguration* pConfig, int priority, bool writeable, bool shared)
{
	ConfigItem item;
	item.pConfig   = ConfigPtr(pConfig, shared);
	item.priority  = priority;
	item.writeable = writeable;

	ConfigList::iterator it = _configs.begin();
	while (it != _configs.end() && it->priority < priority)
		++it;

	_configs.insert(it, item);
}
