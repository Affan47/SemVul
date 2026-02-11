decrRefCount(void *obj) {
    robj *o = obj;


    if (server.vm_enabled &&
        (o->storage == REDIS_VM_SWAPPED || o->storage == REDIS_VM_LOADING))
    {
        vmpointer *vp = obj;
        if (o->storage == REDIS_VM_LOADING) vmCancelThreadedIOJob(o);
        vmMarkPagesFree(vp->page,vp->usedpages);
        server.vm_stats_swapped_objects--;
        zfree(vp);
        return;
    }

    if (o->refcount <= 0) redisPanic("decrRefCount against refcount <= 0");


    if (server.vm_enabled && o->storage == REDIS_VM_SWAPPING)
        vmCancelThreadedIOJob(o);
    if (--(o->refcount) == 0) {
        switch(o->type) {
        case REDIS_STRING: freeStringObject(o); break;
        case REDIS_LIST: freeListObject(o); break;
        case REDIS_SET: freeSetObject(o); break;
        case REDIS_ZSET: freeZsetObject(o); break;
        case REDIS_HASH: freeHashObject(o); break;
        default: redisPanic("Unknown object type"); break;
        }
        o->ptr = NULL;
        zfree(o);
    }
}
