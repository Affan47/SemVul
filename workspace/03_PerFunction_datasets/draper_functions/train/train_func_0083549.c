replconfCommand(redisClient *c) {
    int j;

    if ((c->argc % 2) == 0) {


        addReply(c,shared.syntaxerr);
        return;
    }


    for (j = 1; j < c->argc; j+=2) {
        if (!strcasecmp(c->argv[j]->ptr,"listening-port")) {
            long port;

            if ((getLongFromObjectOrReply(c,c->argv[j+1],
                    &port,NULL) != REDIS_OK))
                return;
            c->slave_listening_port = port;
        } else {
            addReplyErrorFormat(c,"Unrecognized REPLCONF option: %s",
                (char*)c->argv[j]->ptr);
            return;
        }
    }
    addReply(c,shared.ok);
}
