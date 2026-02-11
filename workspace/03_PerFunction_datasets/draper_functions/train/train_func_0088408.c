convert(tstring & result,
    const spi::InternalLoggingEvent& event)
{
    const tstring& name = event.getLoggerName();
    if (precision <= 0) {
        result = name;
    }
    else {
        size_t len = name.length();


        tstring::size_type end = len - 1;
        for (int i = precision; i > 0; --i)
        {
            end = name.rfind(DCMTK_LOG4CPLUS_TEXT('.'), end - 1);
            if(end == OFString_npos) {
                result = name;
                return;
            }
        }
        result = name.substr(end + 1);
    }
}
