sentinelFailoverReconfNextSlave(sentinelRedisInstance *master) {
    dictIterator *di;
    dictEntry *de;
    int in_progress = 0;

    di = dictGetIterator(master->slaves);
    while((de = dictNext(di)) != NULL) {
        sentinelRedisInstance *slave = dictGetVal(de);

        if (slave->flags & (SRI_RECONF_SENT|SRI_RECONF_INPROG))
            in_progress++;
    }
    dictReleaseIterator(di);

    di = dictGetIterator(master->slaves);
    while(in_progress < master->parallel_syncs &&
          (de = dictNext(di)) != NULL)
    {
        sentinelRedisInstance *slave = dictGetVal(de);
        int retval;
        char master_port[32];


        if (slave->flags & (SRI_PROMOTED|SRI_RECONF_DONE)) continue;


        if ((slave->flags & SRI_RECONF_SENT) &&
            (mstime() - slave->slave_reconf_sent_time) >
            SENTINEL_SLAVE_RECONF_RETRY_PERIOD)
        {
            sentinelEvent(REDIS_NOTICE,"-slave-reconf-sent-timeout",slave,"%@");
            slave->flags &= ~SRI_RECONF_SENT;
        }


        if (slave->flags & (SRI_DISCONNECTED|SRI_RECONF_SENT|SRI_RECONF_INPROG))
            continue;


        ll2string(master_port,sizeof(master_port),
            master->promoted_slave->addr->port);
        retval = redisAsyncCommand(slave->cc,
            sentinelDiscardReplyCallback, NULL, "SLAVEOF %s %s",
                master->promoted_slave->addr->ip,
                master_port);
        if (retval == REDIS_OK) {
            slave->flags |= SRI_RECONF_SENT;
            slave->pending_commands++;
            slave->slave_reconf_sent_time = mstime();
            sentinelEvent(REDIS_NOTICE,"+slave-reconf-sent",slave,"%@");
            in_progress++;
        }
    }
    dictReleaseIterator(di);
    sentinelFailoverDetectEnd(master);
}
