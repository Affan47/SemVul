replicationCron(void) {

    if (server.masterhost &&
        (server.repl_state == REDIS_REPL_CONNECTING ||
         server.repl_state == REDIS_REPL_RECEIVE_PONG) &&
        (time(NULL)-server.repl_transfer_lastio) > server.repl_timeout)
    {
        redisLog(REDIS_WARNING,"Timeout connecting to the MASTER...");
        undoConnectWithMaster();
    }


    if (server.masterhost && server.repl_state == REDIS_REPL_TRANSFER &&
        (time(NULL)-server.repl_transfer_lastio) > server.repl_timeout)
    {
        redisLog(REDIS_WARNING,"Timeout receiving bulk data from MASTER... If the problem persists try to set the 'repl-timeout' parameter in redis.conf to a larger value.");
        replicationAbortSyncTransfer();
    }


    if (server.masterhost && server.repl_state == REDIS_REPL_CONNECTED &&
        (time(NULL)-server.master->lastinteraction) > server.repl_timeout)
    {
        redisLog(REDIS_WARNING,"MASTER time out: no data nor PING received...");
        freeClient(server.master);
    }


    if (server.repl_state == REDIS_REPL_CONNECT) {
        redisLog(REDIS_NOTICE,"Connecting to MASTER...");
        if (connectWithMaster() == REDIS_OK) {
            redisLog(REDIS_NOTICE,"MASTER <-> SLAVE sync started");
        }
    }


    if (!(server.cronloops % (server.repl_ping_slave_period * server.hz))) {
        listIter li;
        listNode *ln;

        listRewind(server.slaves,&li);
        while((ln = listNext(&li))) {
            redisClient *slave = ln->value;


            if (slave->replstate == REDIS_REPL_SEND_BULK) continue;
            if (slave->replstate == REDIS_REPL_ONLINE) {

                addReplySds(slave,sdsnew("*1\r\n$4\r\nPING\r\n"));
            } else {


                if (write(slave->fd, "\n", 1) == -1) {

                }
            }
        }
    }
}
