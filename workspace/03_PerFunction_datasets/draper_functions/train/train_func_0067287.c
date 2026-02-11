handleBeginCollectiveOperation( void *firsthandlerarg, uint64_t time, uint32_t process,
    uint32_t collOp, uint64_t matchingId, uint32_t procGroup, uint32_t rootProc,
    uint64_t sent, uint64_t received, uint32_t scltoken, OTF_KeyValueList *kvlist ) {


    Control* control= (Control*) firsthandlerarg;

    while ( control->checkTime( time ) )
        ;

    if ( control->doSnapshots && control->aux_state ) {
	OTFAUX_State_processBeginCollectiveOperation( control->aux_state,
	                                              time,
	                                              process,
	                                              procGroup,
	                                              rootProc,
	                                              collOp,
	                                              matchingId,
	                                              sent,
	                                              received,
	                                              scltoken,
	                                              OTF_KeyValueList_clone( kvlist ) );
    }

    if ( control->stats )
	control->stats->beginCollOperation( process, rootProc,
	collOp,matchingId, sent, received );

    if ( control->copyEvents )
	return OTF_CopyHandler_BeginCollectiveOperation( control->writer, time,
	                                                 process, collOp,
	                                                 matchingId, procGroup,
	                                                 rootProc, sent,
	                                                 received, scltoken,
	                                                 kvlist );

        return OTF_RETURN_OK;

}
