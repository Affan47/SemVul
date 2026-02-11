threadStartFuncWorker(void * arg)
#elif defined(LOG4CPLUS_USE_WIN32_THREADS) && defined (_WIN32_WCE)
DWORD
ThreadStart::threadStartFuncWorker(void * arg)
#elif defined(LOG4CPLUS_USE_WIN32_THREADS)
unsigned
ThreadStart::threadStartFuncWorker(void * arg)
#endif
{
    blockAllSignals ();
    helpers::SharedObjectPtr<helpers::LogLog> loglog
        = helpers::LogLog::getLogLog();
    if (! arg)
        loglog->error(LOG4CPLUS_TEXT("threadStartFunc()- arg is NULL"));
    else
    {
        AbstractThread * ptr = static_cast<AbstractThread*>(arg);
        AbstractThreadPtr thread(ptr);


        ptr->removeReference ();

        try
        {
            thread->run();
        }
        catch(std::exception& e)
        {
            tstring err = LOG4CPLUS_TEXT("threadStartFunc()- run() terminated with an exception: ");
            err += LOG4CPLUS_C_STR_TO_TSTRING(e.what());
            loglog->warn(err);
        }
        catch(...)
        {
            loglog->warn(LOG4CPLUS_TEXT("threadStartFunc()- run() terminated with an exception."));
        }
        thread->flags &= ~AbstractThread::fRUNNING;
        getNDC().remove();
    }

    return 0;
}
