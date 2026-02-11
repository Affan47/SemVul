load()
	{
		if (mTemplateFileName.empty()) return;

		if (ResourceGroupManager::getSingletonPtr()->resourceExists(ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, mTemplateFileName))
		{
			DataStreamPtr logoCornersFile = ResourceGroupManager::getSingletonPtr()->openResource(mTemplateFileName);
			mTemplate = logoCornersFile->getAsString();
			mHash = calcHash(mTemplate);
		}
	}
