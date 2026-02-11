append(const spi::InternalLoggingEvent& event)
{
    LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( getLogLog().mutex )
        log4cplus::tostream& output = (logToStdErr ? tcerr : tcout);
        layout->formatAndAppend(output, event);
        if(immediateFlush) {
            output.flush();
        }
    LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
}
