startServerFailed()
{
    struct display *d = startingServer;
    if (!d->serverAttempts || d->startTries < d->serverAttempts) {
        d->serverStatus = pausing;
        serverTimeout = d->openDelay + now;
    } else {
        d->serverStatus = ignore;
        serverTimeout = TO_INF;
        startingServer = 0;
        logError("X server for display %s cannot be started,"
                 " session disabled\n", d->name);
        stopDisplay(d);
    }
}
