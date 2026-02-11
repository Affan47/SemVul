replicationCron(void) {

    if (server.masterhost && server.replstate == REDIS_REPL_TRANSFER &&
        (time(NULL)-server.repl_transfer_lastio) > REDIS_REPL_TIMEOUT)
    {
        redisLog(REDIS_WARNING,"Timeout receiving bulk data from MASTER...");
        replicationAbortSyncTransfer();
    }


    if (server.masterhost && server.replstate == REDIS_REPL_CONNECTED &&
        (time(NULL)-server.master->lastinteraction) > REDIS_REPL_TIMEOUT)
    {
        redisLog(REDIS_WARNING,"MASTER time out: no data nor PING received...");
        freeClient(server.master);
    }


    if (server.replstate == REDIS_REPL_CONNECT) {
        redisLog(REDIS_NOTICE,"Connecting to MASTER...");
        if (connectWithMaster() == REDIS_OK) {
            redisLog(REDIS_NOTICE,"MASTER <-> SLAVE sync started");
        }
    }


    if (!(server.cronloops % (REDIS_REPL_PING_SLAVE_PERIOD*10))) {
        listIter li;
        listNode *ln;

        listRewind(server.slaves,&li);
        while((ln = listNext(&li))) {
            redisClient *slave = ln->value;


            if (slave->replstate == REDIS_REPL_SEND_BULK) continue;
            if (slave->replstate == REDIS_REPL_ONLINE) {

                addReplySds(slave,sdsnew("PING\r\n"));
            } else {


                if (write(slave->fd, "\n", 1) == -1) {

                }
            }
        }
    }
}
