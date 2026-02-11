OTFAUX_Process_writeCollOps( OTFAUX_Process* process,
                               uint64_t snapshotTime,
                             void* userData )
{
    int ret = 1;
    int i;
    Stack* entry;

    if ( !process )
        return 0;

    if ( !process->sharedState->writeBeginCollopSnapshot
            && !process->sharedState->writeCollopCountSnapshot )
        return 1;

    entry = stack_next( &process->pendingCollOps );
    while ( ret && entry != &process->pendingCollOps )
    {
        OTFAUX_CollOp* collop = ( OTFAUX_CollOp* )entry;
        entry = stack_next( entry );

        ret = process->sharedState->writeBeginCollopSnapshot( userData,
                                                              snapshotTime,
                                                              collop->eventTime,
                                                              process->id,
                                                              collop->collOp,
                                                              collop->matchingId,
                                                              collop->comm,
                                                              collop->root,
                                                              collop->bytesSent,
                                                              collop->bytesRecv,
                                                              collop->scl,
                                                              collop->eventData );
    }

    for ( i = 0; ret && i < COLLOPCOUNT_HASH_SIZE; i++ )
    {
        OTFAUX_CollOpCount* collop_count = process->collOpCounts[ i ];
        while ( ret && collop_count )
        {
            ret = process->sharedState->writeCollopCountSnapshot( userData,
                                                                  snapshotTime,
                                                                  process->id,
                                                                  collop_count->comm,
                                                                  collop_count->count );

            collop_count = collop_count->next;
        }
    }

    return ret;
}
