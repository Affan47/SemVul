removeAllTemplates(bool deleteTemplate)
    {
        OGRE_LOCK_AUTO_MUTEX;
        if (deleteTemplate)
        {
            ParticleTemplateMap::iterator itr;
            for (itr = mSystemTemplates.begin(); itr != mSystemTemplates.end(); ++itr)
                OGRE_DELETE itr->second;
        }

        mSystemTemplates.clear();
    }
