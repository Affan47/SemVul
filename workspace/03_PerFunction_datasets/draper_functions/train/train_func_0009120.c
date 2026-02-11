pubsubSubscribePattern(redisClient *c, robj *pattern) {
    int retval = 0;

    if (listSearchKey(c->pubsub_patterns,pattern) == NULL) {
        retval = 1;
        pubsubPattern *pat;
        listAddNodeTail(c->pubsub_patterns,pattern);
        incrRefCount(pattern);
        pat = zmalloc(sizeof(*pat));
        pat->pattern = getDecodedObject(pattern);
        pat->client = c;
        listAddNodeTail(server.pubsub_patterns,pat);
    }

    addReply(c,shared.mbulk3);
    addReply(c,shared.psubscribebulk);
    addReplyBulk(c,pattern);
    addReplyLongLong(c,dictSize(c->pubsub_channels)+listLength(c->pubsub_patterns));
    return retval;
}
