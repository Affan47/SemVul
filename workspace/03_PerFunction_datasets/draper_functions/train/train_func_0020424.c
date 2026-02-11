sentinelPublishReplyCallback(redisAsyncContext *c, void *reply, void *privdata) {
    sentinelRedisInstance *ri = c->data;
    redisReply *r;
    REDIS_NOTUSED(privdata);

    if (ri) ri->pending_commands--;
    if (!reply || !ri) return;
    r = reply;


    if (r->type != REDIS_REPLY_ERROR)
        ri->last_pub_time = mstime();
}
