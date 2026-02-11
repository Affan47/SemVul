sentinelFailoverWaitStart(sentinelRedisInstance *ri) {
    char *leader;
    int isleader;


    leader = sentinelGetLeader(ri, ri->failover_epoch);
    isleader = leader && strcasecmp(leader,server.runid) == 0;
    sdsfree(leader);


    if (!isleader && !(ri->flags & SRI_FORCE_FAILOVER)) {
        int election_timeout = SENTINEL_ELECTION_TIMEOUT;


        if (election_timeout > ri->failover_timeout)
            election_timeout = ri->failover_timeout;

        if (mstime() - ri->failover_start_time > election_timeout) {
            sentinelEvent(REDIS_WARNING,"-failover-abort-not-elected",ri,"%@");
            sentinelAbortFailover(ri);
        }
        return;
    }
    sentinelEvent(REDIS_WARNING,"+elected-leader",ri,"%@");
    ri->failover_state = SENTINEL_FAILOVER_STATE_SELECT_SLAVE;
    ri->failover_state_change_time = mstime();
    sentinelEvent(REDIS_WARNING,"+failover-state-select-slave",ri,"%@");
}
