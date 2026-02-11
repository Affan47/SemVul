maStartAppweb(MaAppweb *appweb)
{
    MaServer    *server;
    char        *timeText;
    int         next;

    for (next = 0; (server = mprGetNextItem(appweb->servers, &next)) != 0; ) {
        if (maStartServer(server) < 0) {
            return MPR_ERR_CANT_INITIALIZE;
        }
    }
    timeText = mprGetDate(0);
    mprLog(1, "HTTP services Started at %s with max %d threads", timeText, mprGetMaxWorkers(appweb));
    return 0;
}
