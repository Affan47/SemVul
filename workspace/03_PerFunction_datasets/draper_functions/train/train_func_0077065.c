load(const DataStreamPtr& stream, const String& separators,
        bool trimWhitespace)
    {

        clear();

        String currentSection = BLANKSTRING;
        SettingsMultiMap* currentSettings = OGRE_NEW_T(SettingsMultiMap, MEMCATEGORY_GENERAL)();
        mSettings[currentSection] = currentSettings;


        String line, optName, optVal;
        while (!stream->eof())
        {
            line = stream->getLine();

            if (line.length() > 0 && line.at(0) != '#' && line.at(0) != '@')
            {
                if (line.at(0) == '[' && line.at(line.length()-1) == ']')
                {

                    currentSection = line.substr(1, line.length() - 2);
                    SettingsBySection::const_iterator seci = mSettings.find(currentSection);
                    if (seci == mSettings.end())
                    {
                        currentSettings = OGRE_NEW_T(SettingsMultiMap, MEMCATEGORY_GENERAL)();
                        mSettings[currentSection] = currentSettings;
                    }
                    else
                    {
                        currentSettings = seci->second;
                    }
                }
                else
                {

                    Ogre::String::size_type separator_pos = line.find_first_of(separators, 0);
                    if (separator_pos != Ogre::String::npos)
                    {
                        optName = line.substr(0, separator_pos);

                        Ogre::String::size_type nonseparator_pos = line.find_first_not_of(separators, separator_pos);


                        optVal = (nonseparator_pos == Ogre::String::npos) ? "" : line.substr(nonseparator_pos);
                        if (trimWhitespace)
                        {
                            StringUtil::trim(optVal);
                            StringUtil::trim(optName);
                        }
                        currentSettings->insert(SettingsMultiMap::value_type(optName, optVal));
                    }
                }
            }
        }
    }
