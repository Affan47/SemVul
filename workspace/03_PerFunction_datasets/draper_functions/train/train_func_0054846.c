FileAppender(const Properties& props,
                           STD_NAMESPACE ios_base::openmode mode_)
    : Appender(props)
    , immediateFlush(true)
    , reopenDelay(1)
    , bufferSize (0)
    , buffer (0)
    , out ()
    , filename ()
    , localeName ()
    , reopen_time ()
{
    bool app = (mode_ == STD_NAMESPACE ios::app);
    tstring const & fn = props.getProperty( DCMTK_LOG4CPLUS_TEXT("File") );
    if (fn.empty())
    {
        getErrorHandler()->error( DCMTK_LOG4CPLUS_TEXT("Invalid filename") );
        return;
    }

    props.getBool (immediateFlush, DCMTK_LOG4CPLUS_TEXT("ImmediateFlush"));
    props.getBool (app, DCMTK_LOG4CPLUS_TEXT("Append"));
    props.getInt (reopenDelay, DCMTK_LOG4CPLUS_TEXT("ReopenDelay"));
    props.getULong (bufferSize, DCMTK_LOG4CPLUS_TEXT("BufferSize"));

    tstring lockFileName = props.getProperty (DCMTK_LOG4CPLUS_TEXT ("LockFile"));
    if (useLockFile && lockFileName.empty ())
    {
        lockFileName = fn;
        lockFileName += DCMTK_LOG4CPLUS_TEXT(".lock");
    }

    localeName = props.getProperty (DCMTK_LOG4CPLUS_TEXT ("Locale"),
        DCMTK_LOG4CPLUS_TEXT ("DEFAULT"));

    init(fn, (app ? STD_NAMESPACE ios::app : STD_NAMESPACE ios::trunc), lockFileName);
}
