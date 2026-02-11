ensureInit()
	{
		QMutexLocker locker(&m);
		if(init_done)
			return;
		init_done = true;

		p->init();


		QVariantMap conf = getProviderConfig_internal(p);
		if(!conf.isEmpty())
			p->configChanged(conf);
	}
