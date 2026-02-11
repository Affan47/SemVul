sentinelFailoverSendSlaveOfNoOne(sentinelRedisInstance *ri) {
    int retval;


    if (ri->promoted_slave->flags & SRI_DISCONNECTED) {
        if (mstime() - ri->failover_state_change_time > ri->failover_timeout) {
            sentinelEvent(REDIS_WARNING,"-failover-abort-slave-timeout",ri,"%@");
            sentinelAbortFailover(ri);
        }
        return;
    }


    retval = sentinelSendSlaveOf(ri->promoted_slave,NULL,0);
    if (retval != REDIS_OK) return;
    sentinelEvent(REDIS_NOTICE, "+failover-state-wait-promotion",
        ri->promoted_slave,"%@");
    ri->failover_state = SENTINEL_FAILOVER_STATE_WAIT_PROMOTION;
    ri->failover_state_change_time = mstime();
}
