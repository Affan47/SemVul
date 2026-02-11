finished()
{
    if (d->m_state == d->FinishedCalled) {
        kWarning(7019) << "finished() called twice! Please fix the KIO slave.";
        return;
    } else if (d->m_state == d->ErrorCalled) {
        kWarning(7019) << "finished() called after error()! Please fix the KIO slave.";
        return;
    }

    d->m_state = d->FinishedCalled;
    mIncomingMetaData.clear();
    d->rebuildConfig();
    sendMetaData();
    send( MSG_FINISHED );


    d->sentListEntries=0;
    d->totalSize=0;
    d->inOpenLoop=false;
}
