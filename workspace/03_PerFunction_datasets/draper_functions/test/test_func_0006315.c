pfmergeCommand(redisClient *c) {
    uint8_t max[HLL_REGISTERS];
    struct hllhdr *hdr;
    int j;


    memset(max,0,sizeof(max));
    for (j = 1; j < c->argc; j++) {

        robj *o = lookupKeyRead(c->db,c->argv[j]);
        if (o == NULL) continue;
        if (isHLLObjectOrReply(c,o) != REDIS_OK) return;


        if (hllMerge(max,o) == REDIS_ERR) {
            addReplySds(c,sdsnew(invalid_hll_err));
            return;
        }
    }


    robj *o = lookupKeyWrite(c->db,c->argv[1]);
    if (o == NULL) {


        o = createHLLObject();
        dbAdd(c->db,c->argv[1],o);
    } else {


        o = dbUnshareStringValue(c->db,c->argv[1],o);
    }


    if (hllSparseToDense(o) == REDIS_ERR) {
        addReplySds(c,sdsnew(invalid_hll_err));
        return;
    }


    hdr = o->ptr;
    for (j = 0; j < HLL_REGISTERS; j++) {
        HLL_DENSE_SET_REGISTER(hdr->registers,j,max[j]);
    }
    HLL_INVALIDATE_CACHE(hdr);

    signalModifiedKey(c->db,c->argv[1]);


    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
    server.dirty++;
    addReply(c,shared.ok);
}
