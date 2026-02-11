logResults()
    {

        String indent = "";
        for (uint i = 0; i < hierarchicalLvl; ++i)
        {
            indent = indent + "\t";
        }

        LogManager::getSingleton().logMessage(indent + "Name " + name +
                        " | Min " + StringConverter::toString(history.minTimePercent) +
                        " | Max " + StringConverter::toString(history.maxTimePercent) +
                        " | Avg "+ StringConverter::toString(history.totalTimePercent / history.totalCalls));

        for(ProfileChildren::iterator it = children.begin(); it != children.end(); ++it)
        {
            it->second->logResults();
        }
    }
