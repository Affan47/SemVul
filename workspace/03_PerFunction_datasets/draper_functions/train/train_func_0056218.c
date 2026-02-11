slotResult( KJob * job )
{
    Q_D(ChmodJob);
    removeSubjob(job);
    if ( job->error() )
    {
        setError( job->error() );
        setErrorText( job->errorText() );
        emitResult();
        return;
    }

    switch ( d->state )
    {
        case CHMODJOB_STATE_LISTING:
            d->m_lstItems.removeFirst();
            kDebug(7007) << "-> processList";
            d->_k_processList();
            return;
        case CHMODJOB_STATE_CHMODING:
            kDebug(7007) << "-> chmodNextFile";
            d->chmodNextFile();
            return;
        default:
            assert(0);
            return;
    }
}
