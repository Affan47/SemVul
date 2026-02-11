ConsoleAppender(const log4cplus::helpers::Properties properties)
: Appender(properties),
  logToStdErr(false),
  immediateFlush(false)
{
    tstring val = toLower(properties.getProperty(LOG4CPLUS_TEXT("logToStdErr")));
    if(val == LOG4CPLUS_TEXT("true")) {
        logToStdErr = true;
    }
    if(properties.exists( LOG4CPLUS_TEXT("ImmediateFlush") )) {
        tstring tmp = properties.getProperty( LOG4CPLUS_TEXT("ImmediateFlush") );
        immediateFlush = (toLower(tmp) == LOG4CPLUS_TEXT("true"));
    }
}
