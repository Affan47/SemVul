run()
{
    while (! shouldTerminate.timed_wait (waitMillis))
    {
        bool modified = checkForFileModification();
        if(modified) {

            HierarchyLocker theLock(h);
            lock = &theLock;


            theLock.resetConfiguration();
            reconfigure();
            updateLastModInfo();


            lock = NULL;
        }
    }
}
