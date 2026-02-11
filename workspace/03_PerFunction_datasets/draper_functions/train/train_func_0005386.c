OTFAUX_Process_endCollOp( OTFAUX_Process* process,
                          uint64_t eventTime,
                          uint64_t matchingId )
{
    OTFAUX_CollOp* collop;
    Stack *entry;

    if ( !process )
        return 0;

    entry = stack_next( &process->pendingCollOps );
    while ( entry != &process->pendingCollOps )
    {
        collop = ( OTFAUX_CollOp* )entry;
        entry = stack_next( entry );

        if ( collop->matchingId == matchingId )
        {
            release_event_data( process, collop->eventData );
            stack_remove( &collop->e );
            OTFAUX_Process_countCollOp( process, collop->comm );
            stack_push( &process->sharedState->collOps, &collop->e );
            return 1;
        }
    }


    return 0;
}
