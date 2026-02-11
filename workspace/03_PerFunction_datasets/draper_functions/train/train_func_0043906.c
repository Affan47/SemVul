sentinelPingReplyCallback(redisAsyncContext *c, void *reply, void *privdata) {
    sentinelRedisInstance *ri = c->data;
    redisReply *r;

    if (ri) ri->pending_commands--;
    if (!reply || !ri) return;
    r = reply;

    if (r->type == REDIS_REPLY_STATUS ||
        r->type == REDIS_REPLY_ERROR) {


        if (strncmp(r->str,"PONG",4) == 0 ||
            strncmp(r->str,"LOADING",7) == 0 ||
            strncmp(r->str,"MASTERDOWN",10) == 0)
        {
            ri->last_avail_time = mstime();
        } else {


            if (strncmp(r->str,"BUSY",4) == 0 &&
                (ri->flags & SRI_S_DOWN) &&
                !(ri->flags & SRI_SCRIPT_KILL_SENT))
            {
                redisAsyncCommand(ri->cc,
                    sentinelDiscardReplyCallback, NULL, "SCRIPT KILL");
                ri->flags |= SRI_SCRIPT_KILL_SENT;
            }
        }
    }
    ri->last_pong_time = mstime();
}
