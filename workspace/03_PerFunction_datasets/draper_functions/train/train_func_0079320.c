convert
                                            (const InternalLoggingEvent& event)
{
    const log4cplus::tstring& name = event.getLoggerName();
    if (precision <= 0) {
        return name;
    }
    else {
        size_t len = name.length();


        tstring::size_type end = len - 1;
        for(int i=precision; i>0; --i) {
            end = name.rfind(LOG4CPLUS_TEXT('.'), end - 1);
            if(end == OFString_npos) {
                return name;
            }
        }
        return name.substr(end + 1);
    }
}
