sentinelReconnectInstance(sentinelRedisInstance *ri) {
    if (!(ri->flags & SRI_DISCONNECTED)) return;


    if (ri->cc == NULL) {
        ri->cc = redisAsyncConnect(ri->addr->ip,ri->addr->port);
        if (ri->cc->err) {
            sentinelEvent(REDIS_DEBUG,"-cmd-link-reconnection",ri,"%@ #%s",
                ri->cc->errstr);
            sentinelKillLink(ri,ri->cc);
        } else {
            ri->cc_conn_time = mstime();
            ri->cc->data = ri;
            redisAeAttach(server.el,ri->cc);
            redisAsyncSetConnectCallback(ri->cc,
                                            sentinelLinkEstablishedCallback);
            redisAsyncSetDisconnectCallback(ri->cc,
                                            sentinelDisconnectCallback);
            sentinelSendAuthIfNeeded(ri,ri->cc);
        }
    }

    if ((ri->flags & SRI_MASTER) && ri->pc == NULL) {
        ri->pc = redisAsyncConnect(ri->addr->ip,ri->addr->port);
        if (ri->pc->err) {
            sentinelEvent(REDIS_DEBUG,"-pubsub-link-reconnection",ri,"%@ #%s",
                ri->pc->errstr);
            sentinelKillLink(ri,ri->pc);
        } else {
            int retval;

            ri->pc_conn_time = mstime();
            ri->pc->data = ri;
            redisAeAttach(server.el,ri->pc);
            redisAsyncSetConnectCallback(ri->pc,
                                            sentinelLinkEstablishedCallback);
            redisAsyncSetDisconnectCallback(ri->pc,
                                            sentinelDisconnectCallback);
            sentinelSendAuthIfNeeded(ri,ri->pc);

            retval = redisAsyncCommand(ri->pc,
                sentinelReceiveHelloMessages, NULL, "SUBSCRIBE %s",
                    SENTINEL_HELLO_CHANNEL);
            if (retval != REDIS_OK) {


                sentinelKillLink(ri,ri->pc);
                return;
            }
        }
    }


    if (ri->cc && (ri->flags & (SRI_SLAVE|SRI_SENTINEL) || ri->pc))
        ri->flags &= ~SRI_DISCONNECTED;
}
