relayEvent(MprList *groups, MprThread *tp)
{
    MprTestGroup    *gp;

    gp = mprGetFirstItem(groups);
    mprAssert(gp);

    mprRelayEvent(gp->dispatcher, runTestThread, groups, NULL);
    if (tp) {
        adjustThreadCount(-1);
    }
}
