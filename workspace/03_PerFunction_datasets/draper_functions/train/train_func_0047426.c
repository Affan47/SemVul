createInstanceImpl( const String& name,
            const NameValuePairList* params)
    {
        if (params != 0)
        {
            NameValuePairList::const_iterator ni = params->find("templateName");
            if (ni != params->end())
            {
                String templateName = ni->second;

                return ParticleSystemManager::getSingleton().createSystemImpl(
                        name, templateName);
            }
        }

        size_t quota = 500;
        String resourceGroup = ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
        if (params != 0)
        {
            NameValuePairList::const_iterator ni = params->find("quota");
            if (ni != params->end())
            {
                quota = StringConverter::parseUnsignedInt(ni->second);
            }
            ni = params->find("resourceGroup");
            if (ni != params->end())
            {
                resourceGroup = ni->second;
            }
        }

        return ParticleSystemManager::getSingleton().createSystemImpl(
                name, quota, resourceGroup);


    }
