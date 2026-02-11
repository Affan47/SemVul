click(int button, int time, unsigned int mods) {


        size_t found;
        size_t pos = FbTk::StringUtil::findCharFromAlphabetAfterTrigger(
                m_tool.timeFormat(), '%', SWITCHES_24_12H, sizeof(SWITCHES_24_12H), &found);

        if (pos != std::string::npos) {
            std::string newformat = m_tool.timeFormat();
            newformat[pos+1] = SWITCHES_12_24H[found];

            if (found < 3) {
                pos = FbTk::StringUtil::findCharFromAlphabetAfterTrigger(
                    newformat, '%', SWITCH_AM_PM, sizeof(SWITCH_AM_PM), 0);
                if (pos != std::string::npos) {
                    newformat.erase(pos, 2);
                }
            }

            m_tool.setTimeFormat(newformat);
            setClockModeLabel();

        }
        FbTk::MenuItem::click(button, time, mods);
    }
