bitcountCommand(redisClient *c) {
    robj *o;
    long start, end, strlen;
    unsigned char *p;
    char llbuf[32];


    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_STRING)) return;


    if (o->encoding == REDIS_ENCODING_INT) {
        p = (unsigned char*) llbuf;
        strlen = ll2string(llbuf,sizeof(llbuf),(long)o->ptr);
    } else {
        p = (unsigned char*) o->ptr;
        strlen = sdslen(o->ptr);
    }


    if (c->argc == 4) {
        if (getLongFromObjectOrReply(c,c->argv[2],&start,NULL) != REDIS_OK)
            return;
        if (getLongFromObjectOrReply(c,c->argv[3],&end,NULL) != REDIS_OK)
            return;

        if (start < 0) start = strlen+start;
        if (end < 0) end = strlen+end;
        if (start < 0) start = 0;
        if (end < 0) end = 0;
        if (end >= strlen) end = strlen-1;
    } else if (c->argc == 2) {

        start = 0;
        end = strlen-1;
    } else {

        addReply(c,shared.syntaxerr);
        return;
    }


    if (start > end) {
        addReply(c,shared.czero);
    } else {
        long bytes = end-start+1;

        addReplyLongLong(c,popcount(p+start,bytes));
    }
}
