memPoolDestroy(MemPool * pool)
{
    int i;
    assert(pool);
    for (i = 0; i < Pools.count; i++) {
	if (Pools.items[i] == pool) {
	    Pools.items[i] = NULL;
	    break;
	}
    }
    stackClean(&pool->pstack);
    xfree(pool);
}
