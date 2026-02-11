setLoggingEvent (const log4cplus::tstring & logger,
    LogLevel loglevel, const log4cplus::tstring & msg, const char * filename,
    int fline)
{


    loggerName = logger;
    ll = loglevel;
    message = msg;
    timestamp = helpers::Time::gettimeofday();
    if (filename)
        file = DCMTK_LOG4CPLUS_C_STR_TO_TSTRING (filename);
    else
        file.clear ();
    line = fline;
    threadCached = false;
    thread2Cached = false;
    ndcCached = false;
    mdcCached = false;
}
