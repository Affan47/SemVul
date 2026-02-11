lrangeCommand(redisClient *c) {
    robj *o;
    long start;
    long end;
    int llen;
    int rangelen;

    if ((getLongFromObjectOrReply(c, c->argv[2], &start, NULL) != REDIS_OK) ||
        (getLongFromObjectOrReply(c, c->argv[3], &end, NULL) != REDIS_OK)) return;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk)) == NULL
         || checkType(c,o,REDIS_LIST)) return;
    llen = listTypeLength(o);


    if (start < 0) start = llen+start;
    if (end < 0) end = llen+end;
    if (start < 0) start = 0;


    if (start > end || start >= llen) {
        addReply(c,shared.emptymultibulk);
        return;
    }
    if (end >= llen) end = llen-1;
    rangelen = (end-start)+1;


    addReplyMultiBulkLen(c,rangelen);
    if (o->encoding == REDIS_ENCODING_ZIPLIST) {
        unsigned char *p = ziplistIndex(o->ptr,start);
        unsigned char *vstr;
        unsigned int vlen;
        long long vlong;

        while(rangelen--) {
            ziplistGet(p,&vstr,&vlen,&vlong);
            if (vstr) {
                addReplyBulkCBuffer(c,vstr,vlen);
            } else {
                addReplyBulkLongLong(c,vlong);
            }
            p = ziplistNext(o->ptr,p);
        }
    } else if (o->encoding == REDIS_ENCODING_LINKEDLIST) {
        listNode *ln;


        if (start > llen/2) start -= llen;
        ln = listIndex(o->ptr,start);

        while(rangelen--) {
            addReplyBulk(c,ln->value);
            ln = ln->next;
        }
    } else {
        redisPanic("List encoding is not LINKEDLIST nor ZIPLIST!");
    }
}
