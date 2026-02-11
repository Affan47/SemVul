mprGetWorkerServiceStats(MprWorkerService *ws, MprWorkerStats *stats)
{
    mprAssert(ws);

    stats->maxThreads = ws->maxThreads;
    stats->minThreads = ws->minThreads;
    stats->numThreads = ws->numThreads;
    stats->maxUse = ws->maxUseThreads;
    stats->idleThreads = (int) ws->idleThreads->length;
    stats->busyThreads = (int) ws->busyThreads->length;
}
