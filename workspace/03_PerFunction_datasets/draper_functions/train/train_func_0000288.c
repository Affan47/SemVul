FileAppender(const tstring& filename_,
    STD_NAMESPACE ios_base::openmode mode_, bool immediateFlush_)
    : immediateFlush(immediateFlush_)
    , reopenDelay(1)
    , bufferSize (0)
    , buffer (0)
    , out ()
    , filename ()
    , localeName (DCMTK_LOG4CPLUS_TEXT ("DEFAULT"))
    , reopen_time ()
{
    init(filename_, mode_, internal::empty_str);
}
