clear()
{
    thread::MutexGuard guard (hashtable_mutex);

    provisionNodes.erase(provisionNodes.begin(), provisionNodes.end());
    loggerPtrs.erase(loggerPtrs.begin(), loggerPtrs.end());
}
