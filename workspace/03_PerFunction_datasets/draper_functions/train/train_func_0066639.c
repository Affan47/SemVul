httpServerDelayedFinish(HTTPConnectionPtr connection)
{
    TimeEventHandlerPtr handler;

    handler = scheduleTimeEvent(1, httpServerDelayedFinishHandler,
                                sizeof(connection), &connection);
    if(!handler) {
        do_log(L_ERROR,
               "Couldn't schedule delayed finish -- freeing memory.");
        free_chunk_arenas();
        handler = scheduleTimeEvent(1, httpServerDelayedFinishHandler,
                                    sizeof(connection), &connection);
        if(!handler) {
            do_log(L_ERROR,
                   "Couldn't schedule delayed finish -- aborting.\n");
            polipoExit();
        }
    }
}
