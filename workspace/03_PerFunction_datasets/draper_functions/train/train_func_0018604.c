evalShaCommand(redisClient *c) {
    if (sdslen(c->argv[1]->ptr) != 40) {


        addReply(c, shared.noscripterr);
        return;
    }
    evalGenericCommand(c,1);
}
