instance()
{
    if (!s_globalXSyncBasedPoller->q) {
        new XSyncBasedPoller;
    }

    return s_globalXSyncBasedPoller->q;
}
