run()
{
    active = true;
    bool result = false;

#ifdef GC_HAVE_WFAPI
    void *pool;

    if (wizard->deviceTypes.Supported[wizard->current].connector == DEV_BTLE) pool = WFApi::getInstance()->getPool();
#endif

    for (int i=0; active && !result && i<10; i++) {


#ifdef WIN32
        Sleep(1000);
#else
        sleep(1);
#endif
        result = quickScan(false);
    }
    if (active) emit finished(result);

#ifdef GC_HAVE_WFAPI
    WFApi::getInstance()->freePool(pool);
#endif
}
