glueReplyBuffersIfNeeded(redisClient *c) {
    int copylen = 0;
    char buf[GLUEREPLY_UP_TO];
    listNode *ln;
    robj *o;

    listRewind(c->reply);
    while((ln = listYield(c->reply))) {
        int objlen;

        o = ln->value;
        objlen = sdslen(o->ptr);
        if (copylen + objlen <= GLUEREPLY_UP_TO) {
            memcpy(buf+copylen,o->ptr,objlen);
            copylen += objlen;
            listDelNode(c->reply,ln);
        } else {
            if (copylen == 0) return;
            break;
        }
    }

    o = createObject(REDIS_STRING,sdsnewlen(buf,copylen));
    listAddNodeHead(c->reply,o);
}
