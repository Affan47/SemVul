JS_ArenaGrow(JSArenaPool *pool, void *p, size_t size, size_t incr)
{
    void *newp;


    if (size > pool->arenasize)
        return JS_ArenaRealloc(pool, p, size, incr);

    JS_ARENA_ALLOCATE(newp, pool, size + incr);
    if (newp)
        memcpy(newp, p, size);
    return newp;
}
