httpServerGetConnection(HTTPServerPtr server, int *idle_return)
{
    int i, j;
    int connecting = 0, empty = 0, idle = 0;

    j = -1;

    for(i = 0; i < server->numslots; i++) {
        if(server->connection[i]) {
            if(!server->connection[i]->connecting) {
                if(!server->connection[i]->request) {
                    if(server->idleHandler[i])
                        unregisterFdEvent(server->idleHandler[i]);
                    server->idleHandler[i] = NULL;
                    if(j < 0) j = i;
                    idle++;
                }
            } else
                connecting++;
        } else
            empty++;
    }

    if(j >= 0) {
        *idle_return = idle;
        return server->connection[j];
    }


    if(empty) {


        if((connecting == 0 || (server->persistent <= 0 && connecting <= 1)) ||
           connecting < numRequests(server)) {
            httpServerConnection(server);
        }
    }


    if(server->version == HTTP_11 && server->pipeline >= 4) {
        for(i = 0; i < serverSlots; i++) {
            if(server->connection[i] && !server->connection[i]->connecting &&
               pipelineIsSmall(server->connection[i])) {
                if(server->idleHandler[i])
                    unregisterFdEvent(server->idleHandler[i]);
                server->idleHandler[i] = NULL;
                *idle_return = 0;
                return server->connection[i];
            }
        }
    }
    *idle_return = idle;
    return NULL;
}
