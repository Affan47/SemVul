clear(void)
    {
        for (SettingsBySection::iterator seci = mSettings.begin();
            seci != mSettings.end(); ++seci)
        {
             OGRE_DELETE_T(seci->second, SettingsMultiMap, MEMCATEGORY_GENERAL);
        }
        mSettings.clear();
    }
