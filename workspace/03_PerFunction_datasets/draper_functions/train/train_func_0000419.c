setClockModeLabel() {
        _FB_USES_NLS;
        if (FbTk::StringUtil::findCharFromAlphabetAfterTrigger(
            m_tool.timeFormat(), '%', SWITCHES_24_12H, 3, 0) != std::string::npos) {
            setLabel( _FB_XTEXT(Toolbar, Clock24,   "Clock: 24h",   "set Clockmode to 24h") );
        } else {
            setLabel( _FB_XTEXT(Toolbar, Clock12,   "Clock: 12h",   "set Clockmode to 12h") );
        }
    }
