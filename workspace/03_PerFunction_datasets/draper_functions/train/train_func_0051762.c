execCommandReplicateMulti(redisClient *c) {
    robj *multistring = createStringObject("MULTI",5);

    if (server.appendonly)
        feedAppendOnlyFile(server.multiCommand,c->db->id,&multistring,1);
    if (listLength(server.slaves))
        replicationFeedSlaves(server.slaves,c->db->id,&multistring,1);
    decrRefCount(multistring);
}
